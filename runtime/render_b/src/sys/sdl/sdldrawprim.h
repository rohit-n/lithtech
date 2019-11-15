#ifndef LT_SDLDRAWPRIM_H
#define LT_SDLDRAWPRIM_H

// Includes....
#ifndef __ILTDRAWPRIM_H__
#include "iltdrawprim.h"
#endif

#ifndef __GENDRAWPRIM_H__
#include "gendrawprim.h"
#endif

#ifndef __RENDER_H__
#include "render.h"
#endif

#ifndef __DE_OBJECTS_H__
#include "de_objects.h"
#endif

class CSDLDrawPrim : public CGenDrawPrim
{
	public :
		declare_interface(CSDLDrawPrim);

		CSDLDrawPrim();

		virtual LTRESULT BeginDrawPrim();
		virtual LTRESULT EndDrawPrim();
		
		// Sets the current camera to use (viewport, field of view etc)
		virtual LTRESULT SetCamera(const HOBJECT hCamera);

		// Sets current texture
		virtual LTRESULT SetTexture(const HTEXTURE hTexture);

		// Sets transform type
		virtual LTRESULT SetTransformType(const ELTTransformType eType);

		// Sets color operation
		virtual LTRESULT SetColorOp(const ELTColorOp eColorOp);

		// Sets source/dest alpha blending operation
		virtual LTRESULT SetAlphaBlendMode(const ELTBlendMode eBlendMode);

		// Enables/disables z buffering
		virtual LTRESULT SetZBufferMode(const ELTZBufferMode eZBufferMode);

		// Set AlphaTest Mode (on/off)
		virtual LTRESULT SetAlphaTestMode(const ELTTestMode eTestMode);

		// set the type of clipping to be done
		virtual LTRESULT SetClipMode(const ELTClipMode eClipMode);

		// set the fill mode
		virtual LTRESULT SetFillMode(ELTDPFillMode eFillMode);

		// set the cull mode
		virtual LTRESULT SetCullMode(ELTDPCullMode eCullMode);

		// set the fog enable
		virtual LTRESULT SetFogEnable(bool bFogEnable);

        //Specifiy whether or not to be in really close space for rendering
        virtual LTRESULT SetReallyClose(bool bReallyClose);

		virtual LTRESULT SetEffectShaderID(uint32 nEffectShaderID);

		virtual void SetUVWH (LT_POLYGT4 *pPrim, HTEXTURE pTex,
							 float u, float v,
							 float w, float h);

		// store off the current viewport
		virtual void SaveViewport();

		// restore the saved viewport
		virtual void RestoreViewport();

		// Draw primitives (triangles)
		virtual LTRESULT DrawPrim (LT_POLYGT3 *pPrim, 
	                           	const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_POLYFT3 *pPrim, 
	                           	const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_POLYG3 *pPrim, 
	                           	const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_POLYF3 *pPrim, 
	                           	const uint32 nCount = 1);
	
		// Draw primitives (quadrilaterals)
		virtual LTRESULT DrawPrim (LT_POLYGT4 *pPrim, 
	                           	const uint32 nCount = 1);

		virtual LTRESULT DrawPrim (LT_POLYGT4 **ppPrim, 
                                const uint32 nCount = 1);

		virtual LTRESULT DrawPrim (LT_POLYFT4 *pPrim, 
	                           	const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_POLYG4 *pPrim, 
	                           	const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_POLYF4 *pPrim, 
	                           	const uint32 nCount = 1);

		// Draw primitives using lines
		// Note: nCount is Line count.
		virtual LTRESULT DrawPrim (LT_LINEGT *pPrim, 
		                           const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_LINEFT *pPrim, 
		                           const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_LINEG *pPrim, 
		                           const uint32 nCount = 1);
		virtual LTRESULT DrawPrim (LT_LINEF *pPrim, 
		                           const uint32 nCount = 1);

		// Draw primitives using points
		// Note: nCount is Point count.
		virtual LTRESULT DrawPrimPoint (LT_VERTGT *pVerts, 
		                           const uint32 nCount = 1);
		virtual LTRESULT DrawPrimPoint (LT_VERTG *pVerts, 
		                           const uint32 nCount = 1);

		// Draw primitives using triangle fans
		virtual LTRESULT DrawPrimFan (LT_VERTGT *pVerts, 
	                          	  	  const uint32 nCount);
		virtual LTRESULT DrawPrimFan (LT_VERTFT *pVerts, 
	                           		  const uint32 nCount, 
							   		  LT_VERTRGBA rgba);
		virtual LTRESULT DrawPrimFan (LT_VERTG *pVerts, 
	                           		  const uint32 nCount);
		virtual LTRESULT DrawPrimFan (LT_VERTF *pVerts, 
	                           		  const uint32 nCount, 
							   		  LT_VERTRGBA rgba);
	
		// Draw primitives using triangle strips
		virtual LTRESULT DrawPrimStrip (LT_VERTGT *pVerts, 
	                              		const uint32 nCount);
		virtual LTRESULT DrawPrimStrip (LT_VERTFT *pVerts, 
	                           			const uint32 nCount, 
							   			LT_VERTRGBA rgba);
		virtual LTRESULT DrawPrimStrip (LT_VERTG *pVerts, 
	                           			const uint32 nCount);
		virtual LTRESULT DrawPrimStrip (LT_VERTF *pVerts, 
	                           			const uint32 nCount, 
							   			LT_VERTRGBA rgba);

};

#endif // header guard
