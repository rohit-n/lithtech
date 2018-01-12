#include "bdefs.h"

#include "iltclient.h"
#include "console.h"
#include "linuxclientde_impl.h"

//the ILTClient game interface
static ILTClient *ilt_client;
define_holder(ILTClient, ilt_client);

LTRESULT
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
    }

    return LT_ERROR;
}

void cis_Init()
{
    ilt_client->GetEngineHook = cis_GetEngineHook;
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