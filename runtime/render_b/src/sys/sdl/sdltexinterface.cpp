#include "bdefs.h"
#include "ilttexinterface.h"
#include "sdltexinterface.h"
#include "render.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// interface database
define_interface(CSysTexInterface, ILTTexInterface); 

// SharedTexture == SDL_Surface

// Find texture in memory if it exists and return its handle.
// If it does not exist, this function should return an error.
LTRESULT CSysTexInterface::FindTextureFromName(HTEXTURE &hTexture, const char *pFilename) 
{
    hTexture = nullptr;
    return LT_ERROR;
}

LTRESULT CSysTexInterface::CreateTextureFromName(HTEXTURE &hTexture, const char *pFilename)
{
    hTexture = nullptr;
    return LT_ERROR;
}

LTRESULT CSysTexInterface::CreateTextureFromData(HTEXTURE &hTexture, ETextureType eTextureType, uint32 TextureFlags, 
	uint8 *pData, uint32 nWidth, uint32 nHeight, uint32 nAutoGenMipMaps) 
{
    hTexture = nullptr;
    return LT_ERROR;
}

LTRESULT CSysTexInterface::GetTextureData(const HTEXTURE hTexture, const uint8* &pData, uint32 &nPitch, uint32& nWidth, uint32& nHeight, ETextureType& eType) 
{
    return LT_ERROR;
}

LTRESULT CSysTexInterface::FlushTextureData (const HTEXTURE hTexture, ETextureMod eChanged, uint32 nMipMap) 
{
	r_BindTexture(hTexture, true);		 // Bind it to the renderer.
	return LT_OK;
}

LTRESULT CSysTexInterface::GetTextureType(const HTEXTURE hTexture, ETextureType &eTextureType)
{
    return LT_ERROR;
}

LTRESULT CSysTexInterface::GetTextureDims(const HTEXTURE hTexture, uint32 &nWidth, uint32 &nHeight) 
{
    return LT_ERROR;
}

bool CSysTexInterface::ReleaseTextureHandle(const HTEXTURE hTexture)
{
    return false;
}

uint32 CSysTexInterface::AddRefTextureHandle(const HTEXTURE hTexture)
{
    return 0;
}