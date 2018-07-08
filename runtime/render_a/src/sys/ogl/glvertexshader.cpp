#include "glvertexshader.h"


VertexShader::VertexShader()
    : LTVertexShader(),
      m_bCompileShader(false),
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
void VertexShader::FreeDeviceObject()
{}

void VertexShader::SetName(const char*)
{
}

bool VertexShader::GetConstant(unsigned RegisterNum, float *pf0, float *pf1, float *pf2, float *pf3)
{ return false; }
bool VertexShader::SetConstant(unsigned RegisterNum, float f0, float f1, float f2, float f3)
{ return false; }
bool VertexShader::SetConstant(unsigned RegisterNum, const LTMatrix &Matrix)
{ return false; }


VertexShader* createVertexShader()
{
    VertexShader *ptr = new VertexShader{};
    return ptr;
}