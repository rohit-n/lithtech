#ifndef __RENDERSTRUCT_H__
#define __RENDERSTRUCT_H__
#ifndef __PIXELFORMAT_H__
#include "pixelformat.h"
#endif
#ifndef __LIGHTMAPDEFS_H__
#include "lightmapdefs.h"
#endif
class SharedTexture;
class TextureData;
class Attachment;
struct RenderInfoStruct;
#ifndef __RENDEROBJECT_H__
#include "renderobject.h"
#endif
#ifndef NUM_MIPMAPS
    #define NUM_MIPMAPS 8
#endif
#define OPTIMIZE_NO_TRANSPARENCY    0xFFFFFFFF
// Version checking..
#define LTRENDER_VERSION    3421
// Values.
#define RENDER_OK           0
#define RENDER_ERROR        1
// Blit flags.
#define BLIT_TRANSPARENT    1   // Transparent blit.
struct RenderContext;
typedef RenderContext* HRENDERCONTEXT;
// Draw modes.
#define DRAWMODE_NORMAL     1   // Render normally.
#define DRAWMODE_OBJECTLIST 2   // Only render the objects in m_pObjectList.

// This is passed in when rendering a scene.
struct SceneDesc
{
    // How to draw.  One of the DRAWMODE_ defines above.
    int             m_DrawMode;
    // Rendering statistics counters
    uint32          *m_pTicks_Render_Objects;
    uint32          *m_pTicks_Render_Models;
    uint32          *m_pTicks_Render_Sprites;
    uint32          *m_pTicks_Render_WorldModels;
    uint32          *m_pTicks_Render_ParticleSystems;
    LTVector        m_GlobalModelLightAdd;      // Global model light addition.
    // The context gotten from CreateContext.
    HRENDERCONTEXT  m_hRenderContext;
    LTVector        m_GlobalLightScale;     // RGB 0-1, scale / darken the light.
    LTVector        m_GlobalLightAdd;       // RGB 0-1, add / brighten the light.  This
                                            // draws a poly over the screen if one of these
                                            // is nonzero (so it's slower than scale).
    float           m_FrameTime;            // Used for updating things like sprites and texture scripts
    float           m_fActualFrameTime;             // The actual elapsed time. Used for performance measurement.
    // Sky definition and objects.
    SkyDef          m_SkyDef;
    LTObject        **m_SkyObjects;
    int             m_nSkyObjects;
    // Viewport rectangle.
    LTRect          m_Rect;
    // Field of view.
    float           m_xFov, m_yFov;
    // Position info.
    LTVector        m_Pos;
    LTRotation      m_Rotation;
    // Objects to draw, if mode is DRAWMODE_OBJECTSONLY.
    LTObject        **m_pObjectList;
    int             m_ObjectListSize;
    // If ModelHookFn is set, then the renderer will call it before drawing each model.
    void            (*m_ModelHookFn)(ModelHookData *pData, void *pUser);
    void            *m_ModelHookUser;
};
struct RenderStructInit
{
    int     m_RendererVersion;  // The renderer MUST set this to LTRENDER_VERSION.
    RMode   m_Mode;     // What mode we want to use.
                        // The renderer fills in the actual mode that it set.
    void    *m_hWnd;    // The main window.
};
// A blit command.
class BlitRequest {
/*
	HLTBUFFER      m_hBuffer;          // The buffer to blit.
	uint32         m_BlitOptions;      // Combination of the BLIT_ flags above.
	GenericColor   m_TransparentColor; // Transparent color.
	LTRect         *m_pSrcRect;        // Source (m_hBuffer) rectangle.
	LTRect         *m_pDestRect;       // Destination rectangle.
	float          m_Alpha;            // Alpha value (0-1).
*/
}; // stub
struct RenderStruct {
    // Load rendering data from the specified stream
    bool     LoadWorldData(ILTStream *pStream);

    // Functions LithTech implements.
    HRENDERCONTEXT  CreateContext();
    void            DeleteContext(HRENDERCONTEXT hContext);
      // Processes the attachment.  Returns the child object if it exists.
        // Get a shared texture from a file name  (returns NULL on failure)
        // Gets the texture in memory (guaranteed to be in memory until the next
        // call to GetTexture).
		// Gets the texture's file name
        // Force it to free this texture.
        // Runs a string in the console.  The render drivers usually use this
        // so they can get HLTPARAMs right away and not have to check for
        // them all the time.
        // Print a string in the console.
        // Gets a parameter from the game (something that can be set from the console).
        // Returns NULL if the parameter doesn't exist.
        // Gets the value of a parameter .. returns 0/NULL if you pass in NULL.
        // Increments the object frame code.  This is needed for portals.
        // Returns a texture frame code that is guaranteed to not be set in
        // any SharedTextures.  The renderer is expected to set this frame code on
        // any SharedTextures that it uses while rendering so the engine can know
        // if a texture was viewed or not.
    // The engine maintains these variables.
        uint32          m_Width;
        uint32          m_Height;
        int             m_bInitted;
        int             m_bLoaded;
		uint32			m_nIn3D;
		uint32			m_nInOptimized2D;
    // The renderer maintains these.
        uint32  m_SystemTextureMemory;      // How much memory the renderer is using for textures.
    // Functions implemented by the render driver.

        int             Init(RenderStructInit *pInit);   // Returns RENDER_OK for success, or an error code.
//      IDirect3DDevice9* (*GetD3DDevice)(); // Note: In spring the renderer will link directly with the engine.
                            //  RenderStruct will go away - the renderer will be the only thing that
                            //  needs d3d. The DrawPrim interface lives in the engine for now (and it needs the Device).
        // Any textures you expect the renderer to use must be bound and unbound.
        // If bTextureChanged is TRUE, the renderer should reinitialize its data for the texture
        // even if it's already bound.
		//called to set a texture for the draw primitive
        // You render through a context.  Note: LithTech frees all of its lightmap data
        // after calling this because it assumes you converted it all into a more suitable format.
        // Clear a section of the screen.  Flags are from CLEARSCREEN_ flags in de_codes.h.
        // Used around render calls.
        // Render a scene.
        int             RenderScene(SceneDesc *pScene);
        // Handle a command from the console.
        void RenderCommand(uint32 argc, char** argv);
        // Show the backbuffer.
        void            SwapBuffers(uint flags );
        // Get the screen pixel format.
        // Set transparentColor to OPTIMIZE_NO_TRANSPARENCY to not use transparency.
        // Note: whenever you do this, you stall all async performance!
        // Blit a surface to the screen.
        // No clipping is performed so it WILL crash if you don't clip the coordinates!
        // This function CAN be NULL if the driver doesn't want to support this, in
        // which case the engine will just lock the screen and do it itself.
        // Make a screenshot file.
		//Generates a series of images that form a cubic environment map of the form Prefix[FW|BK|LF|RI|UP|DW].bmp
		//aligned along the world's basis space from the given position
        void			(*MakeCubicEnvMap)(const char* pszPrefix, uint32 nSize, const SceneDesc& InSceneDesc);
        // Reads in new console variable values.
        void            (*ReadConsoleVariables)();
        // Get the current render info
        void            GetRenderInfo(RenderInfoStruct* pRenderInfo);
        // Blit from the screen.
        // Creating RenderObjects...
		// Load rendering data from the specified stream
		// Change the color of a lightgroup in the currently loaded world
		// Returns false if a world isn't loaded
        bool SetLightGroupColor(uint32 nID, const LTVector &vColor);
		// Change/query the state of an occluder in the currently loaded world
		// Returns LT_NOTFOUND if the ID isn't found or LT_NOTINWORLD if a world isn't loaded
		LTRESULT SetOccluderEnabled(uint32 nID, bool bEnabled);
		LTRESULT GetOccluderEnabled(uint32 nID, bool *pEnabled);
		// Accessing texture effect variables
		uint32	        GetTextureEffectVarID(const char* pszEffectGroup, uint32 nStage);
		bool			SetTextureEffectVar(uint32 nVarID, uint32 nVar, float fValue);
		// Access to the different object groups
		bool	        IsObjectGroupEnabled(uint32 nGroup);
		void			SetObjectGroupEnabled(uint32 nGroup, bool bEnable);
		void			SetAllObjectGroupEnabled();
		// Access to the render style map used when rendering the glow effect
		bool			AddGlowRenderStyleMapping(const char* pszSource, const char* pszMapTo);
		bool			SetGlowDefaultRenderStyle(const char* pszFile);
		bool			SetNoGlowRenderStyle(const char* pszFile);
        // This stuff MUST come last so it doesn't get zeroed out when switching res.
        int             m_DontClearMarker;

        LTVector		m_GlobalLightDir;
        LTVector		m_GlobalLightColor;
		float			m_GlobalLightConvertToAmbient;
		// Timing variables
		uint32			m_Time_Vis;
}; //stub

// This is what you use to select how you want to initialize the renderer..  Get a list of
// the modes it supports, then copy the desired mode and pass it into RenderStruct::Init().
// Get the list with GetSupportedModes() and pass that into FreeModeList() to free it.
typedef RMode* (*GetSupportedModesFn)();
typedef void (*FreeModeListFn)(RMode *pHead);

// To make a DirectEngine rendering DLL, make a DLL with the function
// "RenderDLLSetup" that looks like this.  This function should init all the
// function pointers in the structure.
typedef void (*RenderDLLSetupFn)(RenderStruct *pStruct);

#endif  // __RENDERSTRUCT_H__
