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

bool CUIVectorFont::CreateFontTextureAndTable(InstalledFontFace&,char const*,bool)
{
    // RKJ Stub return success alway until we start implementing it
    return true;
}

bool
CUIVectorFont::Init(const char *, const char*, uint32, uint8, uint8,LTFontParams*)
{
    // RKJ Stub return success alway until we start implementing it
    return true;
}

bool
CUIVectorFont::Init(const char *, const char*,uint32,const char *,LTFontParams*)
{
    // RKJ Stub return success alway until we start implementing it
    return true;
}

void CUIVectorFont::Term()
{
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

