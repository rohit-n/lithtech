#include "bdefs.h"
#include "dtxmgr.h"
#include "sysstreamsim.h"

#ifndef __CUIDEBUG_H__
#include "cuidebug.h"
#endif

#ifndef __CUIVECTORFONT_H__
#include "cuivectorfont.h"
#endif

#ifndef __LTSYSOPTIM_H__
#include "ltsysoptim.h"
#endif

#include "LTFontParams.h"

#include "iltclient.h"
#include "interface_helpers.h"

#include <string>

// get the ILTTexInterface from the interface database
static ILTTexInterface *pTexInterface = NULL;
define_holder(ILTTexInterface, pTexInterface);

//ILTClient game interface
static ILTClient *ilt_client;
define_holder(ILTClient, ilt_client);


class InstalledFontFace
{
};

bool CUIVectorFont::CreateFontTextureAndTable(InstalledFontFace&,char const*,bool bMakeMap)
{
    // this is an elaborate stub like a null font, defined for every character.
    Term();
    auto nLen = 256;
    LT_MEM_TRACK_ALLOC(m_pFontTable = new uint16[nLen * 3],LT_MEM_TYPE_UI);
    memset(m_pFontTable, 0, sizeof(uint16)*nLen*3);
    if (bMakeMap)
    {
        LT_MEM_TRACK_ALLOC(m_pFontMap = new uint8[nLen],LT_MEM_TYPE_UI);
        m_bAllocatedMap = ( m_pFontMap != nullptr );
    }

    m_Texture = nullptr;
    m_Proportional = true;
    m_Valid = true;

    return true;
}

bool
CUIVectorFont::Init(const char *, const char* face, uint32 pointSize, uint8, uint8,LTFontParams*)
{
    // RKJ Stub return success alway until we start implementing it
    m_PointSize = pointSize;
    InstalledFontFace font;
    return CreateFontTextureAndTable(font, face, true);
}

bool
CUIVectorFont::Init(const char *, const char* face,uint32 pointsize,const char *,LTFontParams*)
{
    // RKJ Stub return success alway until we start implementing it
    return Init("", face, pointsize, 0, 0, nullptr);
}

void CUIVectorFont::Term()
{
    if(m_pFontMap)
        delete[] m_pFontMap;
    if(m_pFontTable)
        delete[] m_pFontTable;

    m_pFontMap = nullptr;
    m_pFontTable = nullptr;
    // RKJ Stub
}

// default constuctor
CUIVectorFont::CUIVectorFont()
{
}

// default destuctor
CUIVectorFont::~CUIVectorFont()
{
}

