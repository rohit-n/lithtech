// ----------------------------------------------------------------------- //
//
// MODULE  : LTGUIMgr.h
//
// PURPOSE : Shared header for the library of LTGUI controls
//
// (c) 1997-2001 Monolith Productions, Inc.  All Rights Reserved
//
// ----------------------------------------------------------------------- //


#if !defined(_LTGUIMGR_H_)
#define _LTGUIMGR_H_


#include "lithtech.h"
#include "iltfontmanager.h"

//TO2 specific 
#include "../../NOLF2/Shared/DebugNew.h"

#pragma warning( disable : 4786 )
#include <vector>

typedef std::vector<CUIPolyString*> PStringArray;
typedef std::vector<CUIFormattedPolyString*> FPStringArray;

//base classes
#include "../LTGUIMgr/ltguicommandhandler.h"
#include "../LTGUIMgr/ltguictrl.h"
typedef std::vector<CLTGUICtrl*> ControlArray;

//basic control classes
#include "../LTGUIMgr/ltguitextitemctrl.h"
#include "../LTGUIMgr/ltguibutton.h"
#include "../LTGUIMgr/ltguicyclectrl.h"
#include "../LTGUIMgr/ltguitoggle.h"
#include "../LTGUIMgr/ltguislider.h"
#include "../LTGUIMgr/ltguicolumnctrl.h"
#include "../LTGUIMgr/ltguiframe.h"
#include "../LTGUIMgr/ltguieditctrl.h"
#include "../LTGUIMgr/ltguilargetext.h"

//container control classes
#include "../LTGUIMgr/ltguiwindow.h"
#include "../LTGUIMgr/ltguilistctrl.h"


//these are defined in the module that links
extern ILTDrawPrim*		g_pDrawPrim;
extern ILTFontManager*	g_pFontManager;
extern ILTTexInterface*	g_pTexInterface;

//utility functions for handling UV coordinates
#include "../LTGUIMgr/ltquaduvutils.h"

#endif // _LTGUIMGR_H_
