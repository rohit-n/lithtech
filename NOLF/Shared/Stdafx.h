// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#ifndef __STDAFX_H__
#define __STDAFX_H__

#define WIN32_LEAN_AND_MEAN

#include <stdio.h>
#include <windows.h>
#include <limits.h>

#include "mfcstub.h"

#include "DebugNew.h"

#include "iltclient.h"
#include "iltserver.h"
#include "iltmessage.h"
#include "globals.h"

#include "iltmodel.h"
#include "ilttransform.h"
#include "iltphysics.h"
#include "iltmath.h"
#include "ltobjectcreate.h"

#include "Factory.h"

#include "CommonUtilities.h"
#include "AutoMessage.h"

inline uint32 GetObjectType(HOBJECT hObj)
{
	ASSERT(g_pCommonLT);

	uint32 nObjType;

	uint32 nResult = g_pCommonLT->GetObjectType(hObj, &nObjType);

	ASSERT(nResult == LT_OK);

	return nObjType;
}

#endif // __STDAFX_H__