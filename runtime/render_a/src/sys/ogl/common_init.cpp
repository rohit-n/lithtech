#include "bdefs.h"

#include "render.h"
#include "ogl_render.h"

static OGlRenderStruct oglrdr;
void oglReadConsoleVariables()
{
  oglrdr.ReadConsoleVariables();
}

void rdll_OGlRenderSetup(RenderStruct *pStruct)
{
    RenderStructInit rsi{LTRENDER_VERSION, false, (void*)&oglrdr};
    if (pStruct->Init(&rsi) == 0)
        pStruct->ReadConsoleVariables = &(oglReadConsoleVariables);
}


void rdll_RenderDLLSetup(RenderStruct *pStruct)
{
    rdll_OGlRenderSetup(pStruct);
}