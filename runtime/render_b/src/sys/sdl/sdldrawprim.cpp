#include "sdldrawprim.h"

define_interface(CSDLDrawPrim, ILTDrawPrim); 
instantiate_interface(CSDLDrawPrim, ILTDrawPrim, Internal);

CSDLDrawPrim::CSDLDrawPrim()
{
}

LTRESULT
CSDLDrawPrim::BeginDrawPrim()
{
    return 0; // rkj rendering stub
}

LTRESULT
CSDLDrawPrim::EndDrawPrim()
{
    return 0; // rkj rendering stub
}

// Sets the current camera to use (viewport, field of view etc)
LTRESULT CSDLDrawPrim::SetCamera(const HOBJECT hCamera)
{
    return 0; // rkj rendering stub
}


// Sets current texture
LTRESULT CSDLDrawPrim::SetTexture(const HTEXTURE hTexture)
{
    return 0; // rkj rendering stub
}


// Sets transform type
LTRESULT CSDLDrawPrim::SetTransformType(const ELTTransformType eType)
{
    return 0; // rkj rendering stub
}


// Sets color operation
LTRESULT CSDLDrawPrim::SetColorOp(const ELTColorOp eColorOp)
{
    return 0; // rkj rendering stub
}


// Sets source/dest alpha blending operation
LTRESULT CSDLDrawPrim::SetAlphaBlendMode(const ELTBlendMode eBlendMode)
{
    return 0; // rkj rendering stub
}


// Enables/disables z buffering
LTRESULT CSDLDrawPrim::SetZBufferMode(const ELTZBufferMode eZBufferMode)
{
    return 0; // rkj rendering stub
}


// Set AlphaTest Mode (on/off)
LTRESULT CSDLDrawPrim::SetAlphaTestMode(const ELTTestMode eTestMode)
{
    return 0; // rkj rendering stub
}


// set the type of clipping to be done
LTRESULT CSDLDrawPrim::SetClipMode(const ELTClipMode eClipMode)
{
    return 0; // rkj rendering stub
}


// set the fill mode
LTRESULT CSDLDrawPrim::SetFillMode(ELTDPFillMode eFillMode)
{
    return 0; // rkj rendering stub
}


// set the cull mode
LTRESULT CSDLDrawPrim::SetCullMode(ELTDPCullMode eCullMode)
{
    return 0; // rkj rendering stub
}


// set the fog enable
LTRESULT CSDLDrawPrim::SetFogEnable(bool bFogEnable)
{
    return 0; // rkj rendering stub
}


//Specifiy whether or not to be in really close space for rendering
LTRESULT CSDLDrawPrim::SetReallyClose(bool bReallyClose)
{
    return 0; // rkj rendering stub
}


LTRESULT CSDLDrawPrim::SetEffectShaderID(uint32 nEffectShaderID)
{
    return 0; // rkj rendering stub
}


void CSDLDrawPrim::SetUVWH (LT_POLYGT4 *pPrim, HTEXTURE pTex,
                        float u, float v,
                        float w, float h)
{
    // rkj rendering stub
}


// store off the current viewport
void CSDLDrawPrim::SaveViewport()
{
    // rkj rendering stub
}


// restore the saved viewport
void CSDLDrawPrim::RestoreViewport()
{
    // rkj rendering stub
}


// Draw primitives (triangles)
LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYGT3 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYFT3 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYG3 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYF3 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}


// Draw primitives (quadrilaterals)
LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYGT4 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}


LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYGT4 **ppPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}


LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYFT4 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYG4 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_POLYF4 *pPrim, 
                        const uint32 nCount)
{
    return 0; // rkj rendering stub
}


// Draw primitives using lines
// Note: nCount is Line count.
LTRESULT CSDLDrawPrim::DrawPrim (LT_LINEGT *pPrim, 
                            const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_LINEFT *pPrim, 
                            const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_LINEG *pPrim, 
                            const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrim (LT_LINEF *pPrim, 
                            const uint32 nCount)
{
    return 0; // rkj rendering stub
}


// Draw primitives using points
// Note: nCount is Point count.
LTRESULT CSDLDrawPrim::DrawPrimPoint (LT_VERTGT *pVerts, 
                            const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrimPoint (LT_VERTG *pVerts, 
                            const uint32 nCount)
{
    return 0; // rkj rendering stub
}


// Draw primitives using triangle fans
LTRESULT CSDLDrawPrim::DrawPrimFan (LT_VERTGT *pVerts, 
                                const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrimFan (LT_VERTFT *pVerts, 
                                const uint32 nCount, 
                                LT_VERTRGBA rgba)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrimFan (LT_VERTG *pVerts, 
                                const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrimFan (LT_VERTF *pVerts, 
                                const uint32 nCount, 
                                LT_VERTRGBA rgba)
{
    return 0; // rkj rendering stub
}


// Draw primitives using triangle strips
LTRESULT CSDLDrawPrim::DrawPrimStrip (LT_VERTGT *pVerts, 
                                const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrimStrip (LT_VERTFT *pVerts, 
                                const uint32 nCount, 
                                LT_VERTRGBA rgba)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrimStrip (LT_VERTG *pVerts, 
                                const uint32 nCount)
{
    return 0; // rkj rendering stub
}

LTRESULT CSDLDrawPrim::DrawPrimStrip (LT_VERTF *pVerts, 
                                const uint32 nCount, 
                                LT_VERTRGBA rgba)
{
    return 0; // rkj rendering stub
}


