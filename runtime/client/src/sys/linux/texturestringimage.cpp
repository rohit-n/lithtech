#include "bdefs.h"
#include "texturestringimage.h"


CTextureStringImage::CTextureStringImage() :
    ILTRefCount{},
	m_pGlyphList{nullptr},
	m_nNumGlyphs{0},
	m_nRowHeight{0}
{
}

CTextureStringImage::~CTextureStringImage() 
{}

const CTextureStringGlyph* CTextureStringImage::GetGlyph(char cGlyph) const
{
    return nullptr;
}

CTextureStringImage* CTextureStringImage::Allocate()
{
    return nullptr;
}
void CTextureStringImage::Free(CTextureStringImage* img)
{}

bool CTextureStringImage::CreateBitmapFont(const char*, const CFontInfo&)
{
    return false;
}
void CTextureStringImage::FreeData()
{}

bool CTextureStringImage::SetupUniqueGlyphList(const char* pszString)
{
    return false;
}
