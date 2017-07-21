#include "bdefs.h"
#include "render.h"
#include "consolecommands.h"
#include "dsys.h"
#include "clientmgr.h"
#include "sysclientde_impl.h"


#ifdef LT_VK_AVAILABLE
VKRenderStruct vkrdr;
#endif
OGlRenderStruct oglrdr;

int RenderStruct::Init(RenderStructInit * pInit)
{
#ifdef LT_VK_AVAILABLE	
	ci_string render(command_line_args->FindArgDash("render"));
	if(render == ci_string("vulkan"))
	    this->m_pRender = &vkrdr;
    else
#endif
         this->m_pRender = &oglrdr;
	pInit->m_RendererVersion = LTRENDER_VERSION;
	return 0;
}

bool RenderStruct::LoadWorldData(ILTStream *pStream)
{
    return this->m_pRender->LoadWorldData(pStream);
}