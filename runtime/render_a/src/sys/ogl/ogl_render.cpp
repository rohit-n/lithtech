#include "bdefs.h"
#include "ogl_render.h"

OGlRenderStruct::OGlRenderStruct()
{
}

bool OGlRenderStruct::LoadWorldData(ILTStream *pStream)
{
    return false; // STUB we currently want to fail loading data;
}

HRENDERCONTEXT OGlRenderStruct::CreateContext()
{
    return nullptr;
}