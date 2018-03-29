#include "bdefs.h"

#include "clientmgr.h"
#include "iltclient.h"
#include "console.h"
#include "bindmgr.h"
#include "linuxclientde_impl.h"

//the ILTClient game interface
static ILTClient *ilt_client;
define_holder(ILTClient, ilt_client);

static LTRESULT
cis_GetEngineHook(const char *name, void **pData)
{
    if(stricmp("hwnd", name) == 0)
    {
		*pData = g_ClientGlob.m_window;
        return LT_OK;
    } else if(stricmp("sdl_window", name) == 0)
    {
		*pData = g_ClientGlob.m_window;
        return LT_OK;
    } else if(stricmp(name, "cshell_hinstance") == 0)
	{
		return bm_GetInstanceHandle(g_pClientMgr->m_hShellModule, pData);
	} else if(stricmp("cres_hinstance", name) == 0)
    {
		return bm_GetInstanceHandle(g_pClientMgr->m_hClientResourceModule, pData);
    }

    return LT_ERROR;
}

void cis_Term()
{}

bool cis_RendererIsHere(RenderStruct *pStruct)
{return false;}
bool cis_RendererGoingAway()
{return false;}

LTRESULT cis_DeleteSurface(HSURFACE hSurface)
{
    return LT_OK; // rkj STUB
}

HSURFACE
cis_CreateSurfaceFromPcx(LoadedBitmap *pBitmap)
{
    return nullptr;
}

static HSURFACE
cis_CreateSurfaceFromBitmap(const char* pBitmap)
{
    return cis_CreateSurfaceFromPcx(nullptr);
}

void cis_Init()
{
    ilt_client->GetEngineHook = cis_GetEngineHook;
    ilt_client->CreateSurfaceFromBitmap = cis_CreateSurfaceFromBitmap;
    ilt_client->DeleteSurface = cis_DeleteSurface;
    
}
