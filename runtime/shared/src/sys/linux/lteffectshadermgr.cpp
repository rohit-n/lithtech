#include "lteffectshadermgr.h"
#include "clientmgr.h"
#include "bindmgr.h"
#include "render.h"

static IRenderer *g_pRender;
define_holder(IRenderer, g_pRender)

LTEffectShaderMgr& LTEffectShaderMgr::GetSingleton()
{
    auto sm = g_pRender->getEffectShaderMgrSingleton();
    return *sm;
}

void LTEffectShaderMgr::RemoveEffectShader(uint32 id)
{
    if(shaders.count(id) > 0){
        delete shaders[id];
        shaders.erase(id);
    }
}
void LTEffectShaderMgr::RemoveAllEffectShaders()
{
    for( auto&& p : shaders)
        delete p.second;
    shaders.clear();
}

LTEffectShader* LTEffectShaderMgr::GetEffectShader(uint32 id)
{
    if(shaders.count(id) == 0)
        return nullptr;
    return shaders[id];
}
