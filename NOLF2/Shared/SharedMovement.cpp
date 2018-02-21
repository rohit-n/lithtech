// ----------------------------------------------------------------------- //
//
// MODULE  : SharedMovement.cpp
//
// PURPOSE : Shared movement implementation.
//
// CREATED : 8/27/99
//
// (c)	1999 Monolith Productions, Inc.  All Rights Reserved
//
// ----------------------------------------------------------------------- //

#include "StdAfx.h"
#include "SharedMovement.h"

#if !defined(_CLIENTBUILD) || defined(__PSX2)

const char* aPPMStrings[] =
{
	"Normal",
	"Snowmobile",
	"Lure",
	"LightCycle"
};

const char* GetPropertyNameFromPlayerPhysicsModel(PlayerPhysicsModel ePPModel)
{
	if (PPM_FIRST <= ePPModel && ePPModel < PPM_NUM_MODELS)
	{
		return aPPMStrings[ePPModel];
	}

    return LTNULL;
}


PlayerPhysicsModel GetPlayerPhysicsModelFromPropertyName(char* pName)
{
	if (!pName) return PPM_NORMAL;

	for (int i = 0; i < PPM_NUM_MODELS; i++)
	{
		if (stricmp(aPPMStrings[i], pName) == 0)
		{
			return (PlayerPhysicsModel)i;
		}
	}

	return PPM_NORMAL;
}

#endif // ! _CLIENTBUILD || __PSX2
