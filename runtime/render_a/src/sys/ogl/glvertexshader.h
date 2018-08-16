
#ifndef __GLVERTEXSHADER_H__
#define __GLVERTEXSHADER_H__

#include "ltbasedefs.h"
#include "ltidtoobjecttable.h"
#include <vector>

struct VertexElement {
    float x, y, z, w;
	float r, g, b, a;
};

struct SysVertexDeclaration;
struct SysVertexShader;

class VertexShader : public LTVertexShader
{
public:
	VertexShader();

	~VertexShader();

	// initialize
	bool							Init(ILTStream *pStream, const VertexElement *pVertexElements,
										 uint32 VertexElementsSize, bool bCompileShader);

	// terminate
	void							Term();

	// recreate the shader interfaces
	bool							Recreate();

	// free the shader interfaces
	void							FreeDeviceObject();

	// is the shader valid
	virtual bool					IsValidShader() const					{ return (NULL != m_pShader && NULL != m_pDeclaration); }

	// id
	void							SetID(uint32 ShaderID)						{ m_ShaderID = ShaderID; }

	// name
	void							SetName(const char *pName);

	// next pointer
	void							SetNext(VertexShader *pNext)		{ m_pNext = pNext; }

	// byte code
	uint8*							GetByteCode()							{ return m_pByteCode.data(); }

	// get the values in a constant register
	virtual bool					GetConstant(unsigned RegisterNum, float *pf0, float *pf1, float *pf2, float *pf3);

	// set the values in a constant register
	virtual bool					SetConstant(unsigned RegisterNum, float f0, float f1, float f2, float f3);

	// copies the values in the given matrix to the four constant registers starting at RegisterNum
	virtual bool					SetConstant(unsigned RegisterNum, const LTMatrix &Matrix);

	// constants
	virtual float*					GetConstants()							{ return m_Constants; }

private:

	bool                            m_bCompileShader;		// this flag specifies whether the shader is already compiled

    std::vector<uint8>              m_pByteCode;
	std::vector<VertexElement>      m_pVertexElements;		// An array of vertex elements used to create the vertex shader declaration

	SysVertexShader*                m_pShader;				// shader interface
	SysVertexDeclaration*           m_pDeclaration;			// d3d vertex shader input declaration interface

	float							m_Constants[LTVertexShader::MAX_CONSTANT_REGISTERS*4];			// user-defined constants
};
#endif
