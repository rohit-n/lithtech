// This file defines DirectEngine's interface to the renderer and holds
// the global RenderStruct used to talk to it.
#ifndef __RENDER_H__
#define __RENDER_H__
#include "ltbasedefs.h"
#include "ltmodule.h"
struct RenderStruct;
struct RMode;
//  Functions that used to be extracted from the render DLL with GetProcAddress
//  but are now staticly linked.
extern RMode* rdll_GetSupportedModes();
extern void rdll_FreeModeList(RMode *pModes);
void rdll_RenderDLLSetup(RenderStruct *pStruct);
/*
#ifdef __ENABLE_VK
#include "vk_render.h"
#endif
*/
#ifdef __ENABLE_OGL
#include "ogl_render.h"
#endif

//  End.
#ifndef __RENDERSTRUCT_H__
#include "renderstruct.h"
#endif

#include <vector>

extern RenderStruct g_Render;
extern RMode        g_RMode;                // The current (or last successful) config for the renderer.
class CClientMgr;
class LTVertexShaderMgr;
class LTPixelShaderMgr;
class LTEffectShaderMgr;


struct BaseShaderInfo
{
    uint32 id;
    ILTStream *file;
    const char *filename;
};

class LTRendererStats;

class IRenderer : public IBase
{
protected:
    RenderStruct *m_pRender;
    RMode        *m_pRMode;
public:
    interface_version(IRenderer, 4);
    virtual ~IRenderer() = default;
    virtual void Update() = 0;
    virtual LTVertexShader* createLTVertexShader(const BaseShaderInfo& bsi, const std::vector<uint32> &elements, bool &compile) = 0;
    virtual LTPixelShader* createEmptyLTPixelShader() = 0;
    virtual LTEffectShader* createEmptyLTEffectShader() = 0;
    virtual LTVertexShaderMgr* getVertexShaderMgrSingleton() = 0;
    virtual LTPixelShaderMgr* getPixelShaderMgrSingleton() = 0;
    virtual LTEffectShaderMgr* getEffectShaderMgrSingleton() = 0;
    virtual RenderStruct* getRenderStruct() = 0;
    virtual int getFrameStats(LTRendererStats&) = 0;
    virtual bool active() = 0;
};


extern IRenderer *g_pRenderer;
// Render initialization status codes.
#define R_OK                    0
#define R_CANTLOADLIBRARY       1
#define R_INVALIDRENDERDLL      2
#define R_INVALIDRENDEROPTIONS  3
// Returns the RenderStruct it's using to talk to the driver.
// Better be initialized...
inline RenderStruct* r_GetRenderStruct() {return g_pRenderer->getRenderStruct();}
inline LTBOOL r_IsRenderInitted() {return g_pRenderer->active();}
// Called right at the beginning by the client.. initializes the RenderStruct
// data members.
void r_InitRenderStruct(bool bFullClear);
// Only implemented for client.exe.. initializes the renderer.
LTRESULT r_InitRender(RMode *pMode, const char* window_name);
// surfaceHandling
//    0 = leave surfaces alone
//    1 = backup surfaces
//    2 = delete surfaces
LTRESULT r_TermRender(int surfaceHandling, bool bUnLoadDLL);
//this should be called to access texture data of a texture. If it has no image and the shared texture
//is properly setup, it will load the image data and bind it to the shared texture
//this should be called to access information on a texture. It will ensure that it is filled out.
//The values are invalid if it returns false
//this will run through and release any textures that have a valid file pointer so that they can
//be recreated later on demand
void r_TerminateAllRecreatableTextureData();
//this will load the texture and bind it to the device. The texture data of the shared texture
//will be valid until it is bound to the device, at which point it is possible that it will
//be freed
//frees the associated texture data and cleans up references to it

//this will bind the texture to the device. Note that the texture data is not guaranteed to be valid
//after this call since the renderer can free it to save memory
void r_BindTexture(SharedTexture *pTexture, bool bTextureChanged);
//unbinds the texture from the device
void r_UnbindTexture(SharedTexture *pTexture, bool bUnloadEngineData);
// Called by the renderer and ILTClient::ProcessAttachments.
LTObject* r_ProcessAttachment(LTObject *pParent, Attachment *pAttachment);

struct SysCache
{
    uint32  m_CurMem;   // How much memory currently used?

    // All the loaded TextureDatas, in an MRU (most recently used are at
    // the start of the list).
    LTList  m_List;
};

extern SysCache g_SysCache;
#endif  // __RENDER_H__
