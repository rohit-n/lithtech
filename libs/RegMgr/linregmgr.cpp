/*
   A registry manager backed by a JSON document
   Rene Kjellerup (c) 2017, 
   release under GNU General Public License version 3 or later
   see https://www.gnu.org/licenses/gpl.html
*/
#include "linregmgr.h"

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <cstdio>

using std::FILE;
using std::fopen;
using std::fclose;
using rapidjson::Document;
using rapidjson::Writer;
using rapidjson::FileReadStream;
using rapidjson::FileWriteStream;
/*
using rapidjson::IStreamWrapper;
using rapidjson::OStreamWrapper;
*/
bool CRegMgr::Init(const char* sCompany, const char* sApp, const char* sVersion, const char* sSubKey, void* hRootKey, char* sRoot2)
{
    FILE *jfp = fopen("LithTech.reg.json", "r");
    if(jfp)
    {
        FileReadStream isw(jfp, iobuffer, sizeof(iobuffer));
        m_Doc.ParseStream(isw);
        fclose(jfp);
    }
    m_bInitialized = true;
    return m_bInitialized;
}

void CRegMgr::Term()
{
    FILE *jfp = fopen("LithTech.reg.json", "w");
    if(jfp)
    {
        FileWriteStream osw(jfp, iobuffer, sizeof(iobuffer));
        Writer<FileWriteStream> writer(osw);
        m_Doc.Accept(writer);
        fclose(jfp);
    }
}

bool CRegMgr::SetSubKey(const char* sSubKey){return true;}
bool CRegMgr::Set(const char* sKey, const char* sValue){return true;}
bool CRegMgr::Set(const char* sKey, void* pValue, int nLen){return true;}
bool CRegMgr::Set(const char* sKey, DWORD nValue){return true;}
const char* CRegMgr::Get(const char* sKey, char* sBuf, UINT32& nBufSize, const char* sDef){return sDef;}
UINT32 CRegMgr::Get(const char* sKey, DWORD nDef){return nDef;}
void* CRegMgr::Get(const char* sKey, void* pBuf, UINT32& nBufSize, void* pDef, UINT32 nDefSize){return pDef;}
bool CRegMgr::Delete(const char* sKey){return true;}
bool CRegMgr::DeleteApp(){return true;}
bool CRegMgr::DeleteSubKey(){return true;}
bool CRegMgr::DeleteUnderSubKey(const char* sKey){return true;}
  