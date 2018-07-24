#include "ltbasedefs.h"


#include "ltvertexshadermgr.h"
#include "clientmgr.h"
#include "bindmgr.h"
#include "render.h"
#include <map>
#include <iterator>

static IRenderer *g_pRender;
define_holder(IRenderer, g_pRender)

LTVertexShaderMgr& LTVertexShaderMgr::GetSingleton()
{
    auto sm = g_pRender->getVertexShaderMgrSingleton();
    return *sm;
}

bool LTVertexShaderMgr::AddVertexShader(ILTStream* file, const char* sname, uint32 id, const uint32 *elements, uint32 &elementSize, bool &bCompileShader)
{
    if(shaders.count(id) > 0)
        return false;
    
    BaseShaderInfo bsi{id, file, sname};
    std::vector<uint32> vtele{elements, elements+elementSize};
    LTVertexShader *s = g_pRender->createLTVertexShader(bsi, vtele, bCompileShader);
    shaders[id] = s; // create the ID entry in the shader map
    return true;
}
void LTVertexShaderMgr::RemoveVertexShader(uint32 id)
{
    if(shaders.count(id) > 0){
        delete shaders[id];
        shaders.erase(id);
    }
}
void LTVertexShaderMgr::RemoveAllVertexShaders()
{
    for( auto&& p : shaders)
        delete p.second;
    shaders.clear();
}

LTVertexShader* LTVertexShaderMgr::GetVertexShader(uint32 id)
{
    if(shaders.count(id) == 0)
        return nullptr;
    return shaders[id];
}
