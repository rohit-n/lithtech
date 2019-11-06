#ifndef WON_MEDIAMETRIX_H
#define WON_MEDIAMETRIX_H
#include "WONShared.h"
#include "WONCommon/Platform.h"
#include <string>

namespace WONAPI
{

#ifdef WIN32
void CreateMediaMetrixEditControl(HWND theParent);
void FillMediaMetrixEditControl(const char *theURL);
void ClearMediaMetrixEditControl();
void DestroyMediaMetrixEditControl();
#endif

};

#endif
