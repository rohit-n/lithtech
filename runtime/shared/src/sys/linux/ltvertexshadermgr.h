#ifndef __LTVERTEXSHADERMGR_H__
#define __LTVERTEXSHADERMGR_H__

#include "ltbasedefs.h"
#include "ltidtoobjecttable.h"
#include <vector>
#include <map>

class VertexElement;
class LTVertexShaderMgr {
	std::map<uint32, LTVertexShader*> shaders;
public:
    static LTVertexShaderMgr& GetSingleton();
    bool AddVertexShader(ILTStream* file, const char* sname, uint32 id, VertexElement *elements, uint32 &size, bool &compile);
    void RemoveVertexShader(uint32 id);
    void RemoveAllVertexShaders();
    LTVertexShader* GetVertexShader(uint32 id);
};

#endif // __LTVERTEXSHADERMGR_H__