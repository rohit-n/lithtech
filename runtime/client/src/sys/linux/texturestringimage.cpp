#include "bdefs.h"
#include "texturestringimage.h"


CTextureStringImage::CTextureStringImage() :
	m_pGlyphList{nullptr},
	m_nNumGlyphs{0},
	m_nRowHeight{0}
{
}

const CTextureStringGlyph* CTextureStringImage::GetGlyph(char cGlyph) const
{
    return nullptr;
}

CTextureStringImage* CTextureStringImage::Allocate()
{
    return nullptr;
}

bool CTextureStringImage::CreateBitmapFont(const char*, const CFontInfo&)
{
    return false;
}