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

void            OGlRenderStruct::DeleteContext(HRENDERCONTEXT hContext){}
int             OGlRenderStruct::RenderScene(SceneDesc *pScene){return 0;}
void            OGlRenderStruct::RenderCommand(uint32 argc, const char** argv){}
void            OGlRenderStruct::SwapBuffers(uint flags ){}
void			OGlRenderStruct::MakeCubicEnvMap(const char* pszPrefix, uint32 nSize, const SceneDesc& InSceneDesc){}
void            OGlRenderStruct::ReadConsoleVariables(){}
void            OGlRenderStruct::GetRenderInfo(RenderInfoStruct* pRenderInfo){}
CRenderObject*  OGlRenderStruct::CreateRenderObject(CRenderObject::RENDER_OBJECT_TYPES ObjectType){return nullptr;}
bool            OGlRenderStruct::DestroyRenderObject(CRenderObject* pObject){return true;}
bool            OGlRenderStruct::SetLightGroupColor(uint32 nID, const LTVector &vColor){return true;}
LTRESULT        OGlRenderStruct::SetOccluderEnabled(uint32 nID, bool bEnabled){return LT_OK;}
LTRESULT        OGlRenderStruct::GetOccluderEnabled(uint32 nID, bool *pEnabled){ *pEnabled=false; return LT_OK; }
uint32	        OGlRenderStruct::GetTextureEffectVarID(const char* pszEffectGroup, uint32 nStage){return 0;}
bool			OGlRenderStruct::SetTextureEffectVar(uint32 nVarID, uint32 nVar, float fValue){return true;}
bool	        OGlRenderStruct::IsObjectGroupEnabled(uint32 nGroup){return false;}
void			OGlRenderStruct::SetObjectGroupEnabled(uint32 nGroup, bool bEnable){}
void			OGlRenderStruct::SetAllObjectGroupEnabled(){}
bool			OGlRenderStruct::AddGlowRenderStyleMapping(const char* pszSource, const char* pszMapTo){return true;}
bool			OGlRenderStruct::SetGlowDefaultRenderStyle(const char* pszFile){return true;}
bool			OGlRenderStruct::SetNoGlowRenderStyle(const char* pszFile){return true;}
