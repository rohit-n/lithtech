#ifndef ___LT_EFFECT_SHADER_MANAGER_H
#define ___LT_EFFECT_SHADER_MANAGER_H

#include "ltbasedefs.h"
#include "ltidtoobjecttable.h"
#include <map>

class LTEffectShader;

class LTEffectShaderMgr {
    std::map<uint32, LTEffectShader*> shaders;
public:
    ~LTEffectShaderMgr(){RemoveAllEffectShaders();}
    static LTEffectShaderMgr& GetSingleton();
    bool AddEffectShader(ILTStream* file, const char* sname, uint32 id, bool compile);
    void RemoveEffectShader(uint32 id);
    void RemoveAllEffectShaders();
    LTEffectShader* GetEffectShader(uint32 id);
};
#endif