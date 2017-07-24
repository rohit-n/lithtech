#include "bdefs.h"

#include "ltvertexshadermgr.h"
#include <map>

	VertexShader::VertexShader()
		: m_bCompileShader(false),
	      m_pByteCode{},
		  m_pVertexElements{},
		  m_pShader(nullptr),
		  m_pDeclaration(nullptr)
	{
	}

	VertexShader::~VertexShader()
	{
		Term();
	}

bool VertexShader::Init(ILTStream *pStream,const VertexElement *elements,uint32 elementSize, bool compileShader)
{
    Term();
    memset(m_Constants,0,sizeof(m_Constants));
    m_bCompileShader = compileShader;
    uint32 len = pStream->GetLen() + 4;
    m_pByteCode.reserve(len);
    if(pStream->Read(m_pByteCode.data(), len) != LT_OK)
    {
        Term();
        return false;
    }
    if(elements == nullptr){
        Term();
        return false;
    }
    m_pVertexElements.reserve(elementSize);
    memcpy(m_pVertexElements.data(), elements, elementSize);

    return Recreate();
}

bool VertexShader::Recreate()
{
    return true;
}

void VertexShader::Term()
{
}

void VertexShader::SetName(const char*)
{
}
class VSMgr : public LTVertexShaderMgr
{
    std::map<uint32,VertexShader*> shaders;
    VSMgr() {};
public:
    static LTVertexShaderMgr& GetSingleton();
    bool AddVertexShader(ILTStream* file, const char* sname, uint32 id, VertexElement *elements, uint32 &size, bool &compile);
    void RemoveVertexShader(uint32 id);
    void RemoveAllVertexShaders();
    VertexShader* GetVertexShader(uint32 id);

};

LTVertexShaderMgr& LTVertexShaderMgr::GetSingleton()
{
    return VSMgr::GetSingleton();
}

LTVertexShaderMgr& VSMgr::GetSingleton()
{
    static VSMgr vertexShaderMgr;
    return vertexShaderMgr;
}
bool VSMgr::AddVertexShader(ILTStream* file, const char* sname, uint32 id, VertexElement *elements, uint32 &elementSize, bool &bCompileShader)
{
    if(shaders.count(id) > 0)
        return false;
    VertexShader *s = new VertexShader();
    s->Init(file, elements, elementSize, bCompileShader);
    s->SetName(sname);
    s->SetID(id);
    shaders[id] = s;
    

    return true;
}
void VSMgr::RemoveVertexShader(uint32 id)
{
    if(shaders.count(id) > 0){
        delete shaders[id];
        shaders.erase(id);
    }
}
void VSMgr::RemoveAllVertexShaders()
{
    for( auto&& p : shaders)
        delete p.second;
    shaders.clear();
}
VertexShader* VSMgr::GetVertexShader(uint32 id)
{
    if(shaders.count(id) == 0)
        return nullptr;
    return shaders[id];
}
