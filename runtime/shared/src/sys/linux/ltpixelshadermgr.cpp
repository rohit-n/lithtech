#include "ltpixelshadermgr.h"
#include "clientmgr.h"
#include "bindmgr.h"
#include "render.h"

static IRenderer *g_pRender;
define_holder(IRenderer, g_pRender)


PixelShader::PixelShader()
: LTPixelShader()
{}

PixelShader::~PixelShader()
{}

bool PixelShader::IsValidShader() const
{
    return true;
}

bool PixelShader::GetConstant(unsigned RegisterNum, float *pf0, float *pf1, float *pf2, float *pf3)
{
    return false;
}
bool PixelShader::SetConstant(unsigned RegisterNum, const LTMatrix &matrix)
{
    return false;
}
bool PixelShader::SetConstant(unsigned RegisterNum, float pf0, float pf1, float pf2, float pf3)
{
    return false;
}

LTPixelShaderMgr::~LTPixelShaderMgr()
{ RemoveAllPixelShaders(); }

LTPixelShaderMgr& LTPixelShaderMgr::GetSingleton()
{
    auto sm = g_pRender->getPixelShaderMgrSingleton();
    return *sm;
}

bool LTPixelShaderMgr::AddPixelShader(ILTStream* file, const char* sname, uint32 id, bool compile)
{
    if(shaders.count(id) > 0)
        return false;
    PixelShader *s = new PixelShader();
    shaders[id] = s;
    return true;
}

void LTPixelShaderMgr::RemoveAllPixelShaders()
{
    for (auto &&s : shaders)
        delete s.second;
    shaders.clear();
}

void LTPixelShaderMgr::RemovePixelShader(uint32 id)
{
    if(shaders.count(id) > 0)
        delete shaders[id];
}


LTPixelShader* LTPixelShaderMgr::GetPixelShader(uint32 id)
{
    if(shaders.count(id) == 0)
        return nullptr;
    return shaders[id];
}
