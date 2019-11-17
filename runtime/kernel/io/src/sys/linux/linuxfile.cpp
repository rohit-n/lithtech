// ------------------------------------------------------------------ //
// Includes..
// ------------------------------------------------------------------ //

#include <sys/stat.h>

#include "bdefs.h"
#include <string.h>
//#include <io.h>
#include <stdio.h>
#include <dirent.h>
#include "sysfile.h"
#include "de_memory.h"
#include "dutil.h"
//#include "dsys_interface.h"
#include "syslthread.h"
#include "syscounter.h"
#include "rezmgr.h"
#include "genltstream.h"

// console output of file access
// 0 - no output (default)
// 1 - display file open calls
// 2 - display file open and close calls
// 3 - display file open and close calls
// 4 - display file open and close and read calls
extern int32 g_CV_ShowFileAccess;

CRezItm* g_pDeFileLastRezItm;
uint32 g_nDeFileLastRezPos;

// PlayDemo profile info.
uint32 g_PD_FOpen=0;


typedef struct FileTree_t
{
	TreeType	m_TreeType;
	CRezMgr*	m_pRezMgr;
	char		m_BaseName[1];
} FileTree;


class BaseFileStream : public CGenLTStream
{
public:

		BaseFileStream()
		{
			m_FileLen = 0;
			m_SeekOffset = 0;
			m_pFile = nullptr;
			m_pTree = nullptr;
			m_ErrorStatus = 0;
			m_nNumReadCalls = 0;
			m_nTotalBytesRead = 0;
			m_pRezItm = nullptr;
		}

	virtual	~BaseFileStream()
	{
		if (g_CV_ShowFileAccess >= 2)
		{
			dsi_ConsolePrint("close stream %p num reads = %u bytes read = %u",
				this, m_nNumReadCalls, m_nTotalBytesRead);
		}

		if(m_pTree->m_TreeType == UnixTree && m_pFile)
		{
			fclose(m_pFile);
		}
	}

	LTRESULT ErrorStatus()
	{
		return m_ErrorStatus ? LT_ERROR : LT_OK;
	}

	LTRESULT GetLen(uint32 *len)
	{
		*len = m_FileLen;
		return LT_OK;
	}

	LTRESULT Write(const void *pData, uint32 dataLen)
	{
		// Can't write to these streams.
		return LT_ERROR;
	}

	unsigned long       m_FileLen;		// Stored when the file is opened.
	unsigned long       m_SeekOffset;	// Seek offset (used in rezfiles) (NOTE: in a rezmgr rez file this is the current position inside the resource).
	FILE*               m_pFile;
	struct FileTree_t*  m_pTree;
	int                 m_ErrorStatus;
	unsigned long       m_nNumReadCalls;
	unsigned long       m_nTotalBytesRead;
	CRezItm*            m_pRezItm;
};


class RezFileStream : public BaseFileStream
{
public:

	RezFileStream() :
	  m_SeekOffset(0)
	{
	}

	void		Release();

	LTRESULT	GetPos(uint32 *pos)
	{
		*pos = m_SeekOffset;
		return LT_OK;
	}

	LTRESULT	SeekTo(uint32 offset)
	{
		if(m_pRezItm->Seek(offset))
		{
			m_SeekOffset = offset;
			return LT_OK;
		}
		else
		{
			m_ErrorStatus = 1;
			return LT_ERROR;
		}
	}

	LTRESULT Read(void *pData, uint32 size)
	{
		size_t sizeRead;

		if(size != 0)
		{
			if ((g_pDeFileLastRezItm == m_pRezItm) && (g_nDeFileLastRezPos == m_SeekOffset))
			{
				sizeRead = m_pRezItm->Read(pData, size);
			}
			else
			{
				sizeRead = m_pRezItm->Read(pData, size, m_SeekOffset);
			}
			
			m_SeekOffset += (uint32)sizeRead;
			g_pDeFileLastRezItm = m_pRezItm;
			g_nDeFileLastRezPos = m_SeekOffset;
			if(sizeRead != size)
			{
				memset(pData, 0, size);
				m_ErrorStatus = 1;
				return LT_ERROR;
			}
		}
		return LT_OK;
	}

	bool IsRawFileInfoAvailable()
	{
		return false;
	}

	LTRESULT GetRawFileInfo(char* sFileName, uint32* nPos)
	{
		return 0;
	}

	uint32		m_SeekOffset;	// Seek offset (used in rezfiles) (NOTE: in a rezmgr rez file this is the current position inside the resource).

};


class UnixFileStream : public BaseFileStream
{
public:

	void	Release();

	LTRESULT GetPos(uint32 *pos)
	{
		*pos = (uint32)(ftell(m_pFile) - m_SeekOffset);
		return LT_OK;
	}

	LTRESULT SeekTo(uint32 offset)
	{
		long ret;

		ret = fseek(m_pFile, offset + m_SeekOffset, SEEK_SET);
		if(ret == 0)
		{
			return LT_OK;
		}
		else
		{
			m_ErrorStatus = 1;
			return LT_ERROR;
		}
	}

	LTRESULT Read(void *pData, uint32 size)
	{
		size_t sizeRead;

		if (g_CV_ShowFileAccess >= 4)
		{
			dsi_ConsolePrint("read %u bytes from stream %p",size, this);
		}

		if(m_ErrorStatus == 1)
		{
			memset(pData, 0, size);
			return LT_ERROR;
		}

		if(size != 0)
		{
			sizeRead = fread(pData, 1, size, m_pFile);
			if(sizeRead == size)
			{
				m_nNumReadCalls++;
				m_nTotalBytesRead += sizeRead;
				return LT_OK;
			}
			else
			{
				memset(pData, 0, size);
				m_ErrorStatus = 1;
				return LT_ERROR;
			}
		}

		return LT_OK;
	}
};

static ObjectBank<UnixFileStream> g_UnixFileStreamBank(8, 8);
static ObjectBank<RezFileStream> g_RezFileStreamBank(8, 8);


void UnixFileStream::Release()
{
	g_UnixFileStreamBank.Free(this);
}

void RezFileStream::Release()
{
	g_RezFileStreamBank.Free(this);
}

// LTFindInfo::m_pInternal..
typedef struct
{
	FileTree		*m_pTree;
	long			m_Handle;
} LTFindData;



// ------------------------------------------------------------------ //
// Interface functions.
// ------------------------------------------------------------------ //

void df_Init()
{
}

void df_Term()
{
}

int df_OpenTree(const char *pName, HLTFileTree *&pTreePointer)
{
	long handle, allocSize;
	FileTree *pTree;
	struct stat info;

	pTreePointer = NULL;

	// See if it exists..
	if (stat(pName,&info) != 0)
		return -1;

	allocSize = sizeof(FileTree) + strlen(pName);
	pTree = (FileTree*)dalloc_z(allocSize);
	if(S_ISDIR(info.st_mode)) {
		pTree->m_TreeType = UnixTree;
	} else if(S_ISREG(info.st_mode)) {
		pTree->m_TreeType = RezFileTree;
		LT_MEM_TRACK_ALLOC(pTree->m_pRezMgr = new CRezMgr(), LT_MEM_TYPE_FILE);
		if (pTree->m_pRezMgr == LTNULL)
			return -2;

		if(!pTree->m_pRezMgr->Open(pName))
		{
			delete pTree->m_pRezMgr;
			dfree(pTree);
			return -2;
		}
	}

	strcpy(pTree->m_BaseName, pName);
	pTreePointer = (HLTFileTree*)pTree;
	return 0;
}


void df_CloseTree(HLTFileTree* hTree)
{
	FileTree *pTree;

	pTree = (FileTree*)hTree;
	if(!pTree)
		return;
	dfree(pTree);
}


TreeType df_GetTreeType(HLTFileTree* hTree)
{
	FileTree *pTree;

	pTree = (FileTree*)hTree;
	if(!pTree)
		return UnixTree;

	return pTree->m_TreeType;
}


void df_BuildName(char *pPart1, char *pPart2, char *pOut)
{
	if(pPart1[0] == 0)
	{
		strcpy(pOut, pPart2);
	}
	else
	{
		sprintf(pOut, "%s/%s", pPart1, pPart2);
	}
}


int df_GetFileInfo(HLTFileTree* hTree, const char *pName, LTFindInfo *pInfo)
{
	FileTree *pTree;
	long handle, curRet;
	char fullName[500];
	CRezItm* pRezItm;

	pTree = (FileTree*)hTree;
	if(!pTree)
		return false;

	if(pTree->m_TreeType == UnixTree)
	{
		sprintf(fullName, "%s/%s", pTree->m_BaseName, pName);
		char* pLastSlash = strrchr(fullName, '/');
		*(pLastSlash++) = '\0';

		int numMatches;
		dirent** namelist;
		if ((numMatches = scandir(fullName, &namelist, 0, alphasort)) > 0)
		{
		        for (int iMatch = 0; iMatch < numMatches; ++iMatch)
			{
				if (namelist[iMatch]->d_type != DT_DIR)
				{
					strncpy(pInfo->m_Name, namelist[iMatch]->d_name, 255);
					pInfo->m_Type = FILE_TYPE;
					//pInfo->m_Size = data.size;
					//memcpy(&pInfo->m_Date, &data.time_write, 4);
					return true;
				}
			}
		}

		// Didn't find any files...
		return false;
	}
	else
	{
		pRezItm = pTree->m_pRezMgr->GetRezFromDosPath(pName);
		if (pRezItm != LTNULL)
		{
			strncpy(pInfo->m_Name, pRezItm->GetName(), sizeof(pInfo->m_Name)-1);
			pInfo->m_Type = FILE_TYPE;
			pInfo->m_Size = pRezItm->GetSize();
			pInfo->m_Date = pRezItm->GetTime();
			return true;
		}
		else
		{
			return false;
		}
	}
}


int df_GetDirInfo(HLTFileTree hTree, char *pName)
{
	FileTree *pTree;
	char fullName[500];
	struct stat info;

	pTree = (FileTree*)hTree;
	if(!pTree) return 0;

	sprintf(fullName, "%s/%s", pTree->m_BaseName, pName);
	if (stat(fullName,&info) != 0) return 0;
	return (S_ISDIR(info.st_mode));
}


int df_GetFullFilename(HLTFileTree hTree, char *pName, char *pOutName, int maxLen)
{
	FileTree *pTree;

	pTree = (FileTree*)hTree;
	if(!pTree)
		return 0;

	if(pTree->m_TreeType != UnixTree)
		return 0;

	sprintf(pOutName, "%s/%s", pTree->m_BaseName, pName);
	return 1;
}


ILTStream* df_Open(HLTFileTree* hTree, const char *pName, int openMode)
{
	char fullName[500];
	FileTree *pTree;
	FILE *fp;
	UnixFileStream *pUnixStream;
	unsigned long seekOffset, fileLen;

	pTree = (FileTree*)hTree;
	if(!pTree)
		return NULL;

	if(pTree->m_TreeType == RezFileTree) {
		CRezItm* pRezItm = pTree->m_pRezMgr->GetRezFromUnixPath(pName);
		if (pRezItm == LTNULL) return LTNULL;
			// Use fp to setup the stream.
		RezFileStream *pRezStream = g_RezFileStreamBank.Allocate();
		pRezStream->m_pRezItm = pRezItm;
		pRezStream->m_pTree = pTree;
		pRezStream->m_FileLen = pRezItm->GetSize();
		pRezStream->m_SeekOffset = 0;

		if (g_CV_ShowFileAccess >= 1)
		{
			dsi_ConsolePrint("stream %p open rez %s size = %u",pRezStream,pName,pRezItm->GetSize());
		}

		return pRezStream;
	}

	if(pTree->m_TreeType != UnixTree) {
		return NULL;
	}

	sprintf(fullName, "%s/%s", pTree->m_BaseName, pName);
	CountAdder cntAdd(&g_PD_FOpen);
	if (! (fp = fopen(fullName, "rb")) )
		return NULL;

	fseek(fp, 0, SEEK_END);
	fileLen = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	seekOffset = 0;

	// Use fp to setup the stream.
	pUnixStream = g_UnixFileStreamBank.Allocate();
	pUnixStream->m_pFile = fp;
	pUnixStream->m_pTree = pTree;
	pUnixStream->m_FileLen = fileLen;
	pUnixStream->m_SeekOffset = seekOffset;

	if (g_CV_ShowFileAccess >= 1)
	{
		dsi_ConsolePrint("stream %p open file %s size = %u",pUnixStream,pName,fileLen);
	}

	return pUnixStream;
}

struct UnixTreeSearch
{
	char searchPath[MAX_PATH];
	DIR* m_pDir;
	UnixTreeSearch(const char* bName, const char *dName)
	{
		memset(searchPath, 0, sizeof(searchPath));
		LTSNPrintF(searchPath, sizeof(searchPath)-1, "%s/%s", bName, dName);
		m_pDir = opendir(searchPath);
	};

	bool GetNextFile(LTFindInfo *pInfo) 
	{
		errno = 0;
		bool found = false;
		dirent64 *pEntry = readdir64(this->m_pDir);
		while(pEntry != nullptr) {
			if (pEntry->d_type == DT_DIR)
				if (pEntry->d_name[0] == '.') { // skip hidden files, '.' and '..' directories
					pEntry = readdir64(this->m_pDir);
					continue;
				}

			if (pEntry->d_type & (DT_REG|DT_DIR|DT_LNK)) 
			{
				found = true;
				break;
			}
			pEntry = readdir64(this->m_pDir);
		}
        if(found) 
			fillFileInfo(pEntry, pInfo);
		return found;
	};
	
	void fillFileInfo(dirent64 *pEntry, LTFindInfo *pInfo)
	{
		char filePath[MAX_PATH];
		struct stat64 st;
		strncpy(pInfo->m_Name, pEntry->d_name, sizeof(pInfo->m_Name)-1);
		pInfo->m_Type = (pEntry->d_type == DT_DIR) ? DIRECTORY_TYPE : FILE_TYPE;
		memset(filePath, 0, sizeof(filePath));
		LTSNPrintF(filePath, sizeof(filePath)-1, "%s/%s", searchPath, pEntry->d_name);
		stat64(filePath, &st);
		pInfo->m_Size = st.st_size;
		pInfo->m_Date = st.st_ctim.tv_sec;
	};

	~UnixTreeSearch()
	{
		closedir(m_pDir);
	};
};


static void cleanUnixTreeSearch(LTFindInfo *pInfo)
{
	UnixTreeSearch *search = reinterpret_cast<UnixTreeSearch*>(pInfo->m_pInternal);
	if(search != nullptr) 
		delete search;
	
	pInfo->m_pInternal = nullptr;
}

static bool findNextUnixTree(const char *pBaseDir, const char *pDirName, LTFindInfo *pInfo)
{
	UnixTreeSearch *search = reinterpret_cast<UnixTreeSearch*>(pInfo->m_pInternal);
	if(search == nullptr) {
		search = new UnixTreeSearch(pBaseDir, pDirName);
		pInfo->m_pInternal = search;
	}
	return search->GetNextFile(pInfo);
}

struct RezSearch
{
	CRezTyp* pCurType=nullptr;
	CRezItm* pCurItm=nullptr;
	CRezDir* pCurDir=nullptr;
	CRezDir* pCurSubDir=nullptr;
	CRezMgr* pRez;
    RezSearch(CRezMgr *mgr) : pRez(mgr) {};
	bool init(const char *pDir) {
		pCurDir = pRez->GetDirFromPath(pDir);
		if (!pCurDir)
			return false;
        return true;
	};
	bool GetNextFile(LTFindInfo *pInfo)	{
		return false;
	}
};

static void cleanRezSearch(LTFindInfo *pInfo)
{
	RezSearch *search = reinterpret_cast<RezSearch*>(pInfo->m_pInternal);
	if(search != nullptr) 
		delete search;
	
	pInfo->m_pInternal = nullptr;
}

static bool findNextRezMgr(CRezMgr *pRez, const char *pDirName, LTFindInfo *pInfo)
{
	RezSearch *search = reinterpret_cast<RezSearch*>(pInfo->m_pInternal);
	if(!search) {
		search = new RezSearch(pRez);
		pInfo->m_pInternal = (void*)search;
		if(!search->init(pDirName))
			return false; // this will call clean Rez and delete the searcher
	} 
	return search->GetNextFile(pInfo);
/*	{
		// If this is the first call to FindNext then set everything up
		if(pInfo->m_pInternal == LTNULL)
		{
			// find the directory
			pRezDir = pRez->GetDirFromPath(pDirName);
			if(pRezDir == LTNULL)
			{
				return 0;
			}

			// get the first type
			pRezTyp = pRezDir->GetFirstType();
			if (pRezTyp != LTNULL)
			{
				// get the first item
				pRezItm = pRezDir->GetFirstItem(pRezTyp);
			}
			else 
			{ 
				pRezItm = LTNULL;
			}

			// if there were no files then get the first sub directory
			if (pRezItm == LTNULL)
			{
				pRezSubDir = pRezDir->GetFirstSubDir();
				if (pRezSubDir == LTNULL)
				{
					return 0;
				}
			}
			else pRezSubDir = LTNULL;

			// allocate the finddata structure
			LT_MEM_TRACK_ALLOC(pFindData = (LTFindData*)dalloc(sizeof(LTFindData)),LT_MEM_TYPE_FILE);
			pInfo->m_pInternal = pFindData;

			// fill in the members of the finddata structure
			pFindData->m_pTree = pTree;
			pFindData->m_pCurDir = pRezDir;
			pFindData->m_pCurTyp = pRezTyp;
			pFindData->m_pCurItm = pRezItm;
			pFindData->m_pCurSubDir = pRezSubDir;
		}

		// If this is not the first call then just get the next entry (or if at end clean up)
		else
		{
			pFindData = (LTFindData*)pInfo->m_pInternal;

			// are we searching for items
			if (pFindData->m_pCurItm != LTNULL)
			{
				pFindData->m_pCurItm = pFindData->m_pCurDir->GetNextItem(pFindData->m_pCurItm);
				
				// if we are finished with all the items of this type go to the next
				while(pFindData->m_pCurItm == LTNULL)
				{
					pFindData->m_pCurTyp = pFindData->m_pCurDir->GetNextType(pFindData->m_pCurTyp);

					// if we are done with all the types then we need to switch to checking sub directories
					if (pFindData->m_pCurTyp == LTNULL)
					{
						pFindData->m_pCurSubDir = pFindData->m_pCurDir->GetFirstSubDir();
						if (pFindData->m_pCurSubDir == LTNULL)
						{
							dfree(pInfo->m_pInternal);
							pInfo->m_pInternal = LTNULL;
							return 0;
						}
						break;
					}

					// get the first item of this type
					else pFindData->m_pCurItm = pFindData->m_pCurDir->GetFirstItem(pFindData->m_pCurTyp);
				}
			}

			// otherwise we are searching for sub directories
			else
			{
				pFindData->m_pCurSubDir = pFindData->m_pCurDir->GetNextSubDir(pFindData->m_pCurSubDir);
				if (pFindData->m_pCurSubDir == LTNULL)
				{
					dfree(pInfo->m_pInternal);
					pInfo->m_pInternal = LTNULL;
					return 0;
				}
			}
		}

		// is this a resource item
		if (pFindData->m_pCurItm != LTNULL)
		{
			LTStrCpy(pInfo->m_Name, pFindData->m_pCurItm->GetName(), sizeof(pInfo->m_Name)-4);
			pTree->m_pRezMgr->TypeToStr(pFindData->m_pCurItm->GetType(),sItemType);
			LTStrCat(pInfo->m_Name, ".", sizeof(pInfo->m_Name));
			LTStrCat(pInfo->m_Name, sItemType, sizeof(pInfo->m_Name));
			pInfo->m_Date = pFindData->m_pCurItm->GetTime();
			pInfo->m_Type = FILE_TYPE;
			pInfo->m_Size = pFindData->m_pCurItm->GetSize();
		}

		// is this a sub directory
		else if (pFindData->m_pCurSubDir != LTNULL)
		{
			LTStrCpy(pInfo->m_Name, pFindData->m_pCurSubDir->GetDirName(), sizeof(pInfo->m_Name));
			pInfo->m_Date = pFindData->m_pCurSubDir->GetTime();
			pInfo->m_Type = DIRECTORY_TYPE;
			pInfo->m_Size = 0;
		}

		else
		{
			return 0; // THIS SHOULD NEVER HAPPEN!
		}

		return 1;
	} */
}


int df_FindNext(HLTFileTree* hTree, const char *pDirName, LTFindInfo *pInfo)
{
	if(!hTree)
		return 0;
	
	FileTree *pTree = reinterpret_cast<FileTree*>(hTree);
	if(pTree->m_TreeType == UnixTree)
	{
		if(findNextUnixTree(pTree->m_BaseName, pDirName, pInfo))
			return 1;
		else {
			cleanUnixTreeSearch(pInfo);
			return 0;
		}
	}
	if(pTree->m_TreeType == RezFileTree)
	{
		if(findNextRezMgr(pTree->m_pRezMgr, pDirName, pInfo))
			return 1;
		else
		    cleanRezSearch(pInfo);
			return 0;
	}
	return 0;
}


void df_FindClose(LTFindInfo *pInfo)
{
}


#define SAVEBUFSIZE 1024*16

// Save the contents of a steam to a file
// returns 1 if successful 0 if an error occured
int df_Save(ILTStream *hFile, const char* pName)
{
	return 0;
}
