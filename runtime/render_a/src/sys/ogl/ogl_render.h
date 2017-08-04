#ifndef __LT_OGL_RENDER_H
#define __LT_OGL_RENDER_H

#include "bdefs.h"
#include "renderstruct.h"

extern void rdll_OGlRenderSetup(RenderStruct *pStruct);

class OGlRenderStruct : public SysRender
{
public:
    OGlRenderStruct();
    bool            LoadWorldData(ILTStream *pStream);
    HRENDERCONTEXT  CreateContext();
    void            DeleteContext(HRENDERCONTEXT hContext);
    uint32          m_Width;
    uint32          m_Height;
    int             m_bInitted;
    int             m_bLoaded;
    uint32			m_nIn3D;
    uint32			m_nInOptimized2D;
    uint32          m_SystemTextureMemory;      // How much memory the renderer is using for textures.
    int             Init(RenderStructInit *pInit);   // Returns RENDER_OK for success, or an error code.
    int             RenderScene(SceneDesc *pScene);
    void            RenderCommand(uint32 argc, const char** argv);
    void            SwapBuffers(uint flags );
    void			MakeCubicEnvMap(const char* pszPrefix, uint32 nSize, const SceneDesc& InSceneDesc);
    void            ReadConsoleVariables();
    void            GetRenderInfo(RenderInfoStruct* pRenderInfo);
    CRenderObject*  CreateRenderObject(CRenderObject::RENDER_OBJECT_TYPES ObjectType);
    bool            DestroyRenderObject(CRenderObject* pObject);
    bool            SetLightGroupColor(uint32 nID, const LTVector &vColor);
    LTRESULT        SetOccluderEnabled(uint32 nID, bool bEnabled);
    LTRESULT        GetOccluderEnabled(uint32 nID, bool *pEnabled);
    uint32	        GetTextureEffectVarID(const char* pszEffectGroup, uint32 nStage);
    bool			SetTextureEffectVar(uint32 nVarID, uint32 nVar, float fValue);
    bool	        IsObjectGroupEnabled(uint32 nGroup);
    void			SetObjectGroupEnabled(uint32 nGroup, bool bEnable);
    void			SetAllObjectGroupEnabled();
    bool			AddGlowRenderStyleMapping(const char* pszSource, const char* pszMapTo);
    bool			SetGlowDefaultRenderStyle(const char* pszFile);
    bool			SetNoGlowRenderStyle(const char* pszFile);
    int             m_DontClearMarker;
    LTVector		m_GlobalLightDir;
    LTVector		m_GlobalLightColor;
    float			m_GlobalLightConvertToAmbient;
    uint32			m_Time_Vis;
};

#endif