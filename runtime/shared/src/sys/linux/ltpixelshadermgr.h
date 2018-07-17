#ifndef __LTPIXELSHADERMGR_H__
#define __LTPIXELSHADERMGR_H__

#include "ltbasedefs.h"
#include "ltidtoobjecttable.h"
#include <map>

class PixelShader: public LTPixelShader
{
    float               m_Constants[LTVertexShader::MAX_CONSTANT_REGISTERS*4];  // user-defined constants
public:
    PixelShader();
    virtual ~PixelShader();
    virtual bool        IsValidShader() const;
	// get the values in a constant register
	virtual bool        GetConstant(unsigned RegisterNum, float *pf0, float *pf1, float *pf2, float *pf3);

	// set the values in a constant register
	virtual bool        SetConstant(unsigned RegisterNum, float f0, float f1, float f2, float f3);

	// copies the values in the given matrix to the four constant registers starting at RegisterNum
	virtual bool        SetConstant(unsigned RegisterNum, const LTMatrix &Matrix);

	// constants
	virtual float*      GetConstants() { return m_Constants; }
};

class LTPixelShaderMgr {
    std::map<uint32, LTPixelShader*> shaders;
public:
    ~LTPixelShaderMgr();
    static LTPixelShaderMgr& GetSingleton();
    bool AddPixelShader(ILTStream* file, const char* sname, uint32 id, bool compile);
    void RemovePixelShader(uint32 id);
    void RemoveAllPixelShaders();
    LTPixelShader* GetPixelShader(uint32 id);
};

#endif // __LTPIXELSHADERMGR_H__