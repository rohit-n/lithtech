#include "bdefs.h"
#include "bindmgr.h"
#include "ltmodule.h"

int bm_BindModule(const char *pModName, bool bTempFile, CBindModuleType *&pModule)
{
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
    return LT_OK;    
}

void* bm_GetFunctionPointer(CBindModuleType *hModule, const char *pFunctionName)
{
    return nullptr;
}