#ifndef __LTPIXELSHADERMGR_H__
#define __LTPIXELSHADERMGR_H__

#include "ltbasedefs.h"
#include "ltidtoobjecttable.h"

class PixelShaderImp: public LTPixelShader
{};

class LTPixelShaderMgr {
public:
    static LTPixelShaderMgr& GetSingleton();
    uint32 AddPixelShader(ILTStream* file, const char* sname, int&, bool);
    void RemovePixelShader(uint32 id);
    void RemoveAllPixelShaders();
    PixelShader* GetPixelShader(uint32 id);
};

#endif // __LTPIXELSHADERMGR_H__