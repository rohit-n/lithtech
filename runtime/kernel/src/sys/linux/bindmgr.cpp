#include "bdefs.h"
#include "bindmgr.h"
#include "ltmodule.h"
#include "syslibraryloader.h"

int bm_BindModule(const char *pModName, bool bTempFile, CBindModuleType *&pModule)
{
	// Check if we already have this module loaded.  If we do
	// then we don't need to do the setmasterdatabase.
	bool bModuleAlreadyLoaded = LTLibraryLoader::IsLibraryLoaded(pModName);
	HLTMODULE hModule = LTLibraryLoader::OpenLibrary(pModName);
	if (hModule == NULL)
	{
		return BIND_CANTFINDMODULE;
    }

	// If this is the first time the module is getting loaded,
	// then tell it about our master database.
	if( !bModuleAlreadyLoaded )
	{
		//merge our interface database with the database in the DLL we just loaded.
		TSetMasterFn pSetMasterFn = (TSetMasterFn)LTLibraryLoader::GetProcAddress(hModule, "SetMasterDatabase");
		
		//check if the function existed.
		if (pSetMasterFn != NULL)
		{
			//merge our database with theirs
			pSetMasterFn(GetMasterDatabase());
		}
	}

	pModule = bm_CreateHandleBinding(bTempFile ? pModName : "", (void*)hModule);
    return 0;
}

void bm_UnbindModule(CBindModuleType *hModule)
{
}

CBindModuleType *bm_CreateHandleBinding(const char *pModuleName, void *pHandle)
{
    return nullptr;
}

LTRESULT bm_SetInstanceHandle(CBindModuleType *hModule)
{
    return LT_OK;
}
LTRESULT bm_GetInstanceHandle(CBindModuleType *hModule, void **pHandle)
{
    *pHandle = nullptr;
    return LT_OK;    
}

void* bm_GetFunctionPointer(CBindModuleType *hModule, const char *pFunctionName)
{
    return nullptr;
}