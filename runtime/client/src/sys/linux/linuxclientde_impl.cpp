#include "bdefs.h"

#include "console.h"
#include "linuxclientde_impl.h"

void cis_Init(ILTClient *pInterface)
{}
void cis_Init()
{
    cis_Init(nullptr);
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