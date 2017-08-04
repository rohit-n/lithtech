#include "bdefs.h"
#include "customfontfilemgr.h"

#include "dsys.h"

CCustomFontFileMgr::CCustomFontFileMgr()
{}
CCustomFontFileMgr::~CCustomFontFileMgr()
{}

CCustomFontFileMgr& CCustomFontFileMgr::GetSingleton(){
    static CCustomFontFileMgr fontMgr{};
    return fontMgr;
}

CCustomFontFile* CCustomFontFileMgr::RegisterCustomFontFile(const char *)
{
    return nullptr;
}

bool CCustomFontFileMgr::UnregisterCustomFontFile(CCustomFontFile *)
{
    return true;
}