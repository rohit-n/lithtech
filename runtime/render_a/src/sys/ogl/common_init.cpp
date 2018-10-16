#include "bdefs.h"

#include "render.h"
#include "ogl_render.h"

define_interface(OGLRenderer, IRenderer)

static OGlRenderStruct oglrdr;
void oglReadConsoleVariables()
{
  oglrdr.ReadConsoleVariables();
}
/*
void rdll_OGlRenderSetup(RenderStruct *pStruct)
{
    RMode e{};
    memset(&e, 0, sizeof(RMode));
    RenderStructInit rsi{0, e, (void*)&oglrdr};
    if (pStruct->Init(&rsi) == 0)
        pStruct->ReadConsoleVariables = &(oglReadConsoleVariables);
}
*/

void rdll_RenderDLLSetup(RenderStruct *pStruct)
{
    pStruct->SetSysRender(oglrdr);
}