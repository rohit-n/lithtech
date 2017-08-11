// ----------------------------------------------------------------------- //
//
// MODULE  : LTGUIMgr.h
//
// PURPOSE : Shared header for the library of LTGUI controls
//
// (c) 1997-2003 Monolith Productions, Inc.  All Rights Reserved
//
// ----------------------------------------------------------------------- //


#if !defined(_LTGUIMGR_H_)
#define _LTGUIMGR_H_


#include "BuildDefines.h"
// #include "engine.h"
#include "ilttexturestring.h"
#include "iltdrawprim.h"

//game specific 
#include "../../Shared/DebugNew.h"
#include "../../Shared/TextureReference.h"
#include "../../Shared/ColorUtilities.h"


#pragma warning( disable : 4786 )
#include <vector>


//base classes
#include "../LTGUIMgr/ltguicommandhandler.h"
#include "../LTGUIMgr/ltguictrl.h"
#include "../LTGUIMgr/ltguistring.h"
#include "../LTGUIMgr/ltguicmds.h"

//basic control classes
#include "../LTGUIMgr/ltguitextctrl.h"
#include "../LTGUIMgr/ltguitexturebutton.h"
#include "../LTGUIMgr/ltguicyclectrl.h"
#include "../LTGUIMgr/ltguitoggle.h"
#include "../LTGUIMgr/ltguislider.h"
#include "../LTGUIMgr/ltguiframe.h"
#include "../LTGUIMgr/ltguieditctrl.h"
#include "../LTGUIMgr/ltguiscrollbar.h"
#include "../LTGUIMgr/ltguiheaderctrl.h"
#include "../LTGUIMgr/ltguifillframe.h"
#include "../LTGUIMgr/ltguitabctrl.h"

//container control classes
#include "../LTGUIMgr/ltguicolumnctrl.h"
#include "../LTGUIMgr/ltguicolumnctrlex.h"
#include "../LTGUIMgr/ltguiwindow.h"
#include "../LTGUIMgr/ltguilistctrl.h"
#include "../LTGUIMgr/ltguilistctrlex.h"

//these are defined in the module that links
extern ILTDrawPrim*		g_pDrawPrim;
extern ILTTextureString* g_pTextureString;
extern ILTTextureMgr*	g_pILTTextureMgr;
extern ILTCSBase* g_pLTBase;

//utility functions for handling UV coordinates
#include "../LTGUIMgr/ltquaduvutils.h"

#endif // _LTGUIMGR_H_
