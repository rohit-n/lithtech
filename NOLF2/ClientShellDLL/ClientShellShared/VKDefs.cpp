//----------------------------------------------------------
//
// MODULE  : VKDefs.cpp
//
// PURPOSE : Keyboard definitions and utilities (Windows-specific)
//
// CREATED : 12/29/97
//
//----------------------------------------------------------

#include "StdAfx.h"
#include "iltclient.h"

char VKToASCII (int nKey)
{
    LTBOOL bShiftDown = IsKeyDown(SDLK_LSHIFT) || IsKeyDown(SDLK_RSHIFT);
    LTBOOL bCapsLockOn = KMOD_CAPS == (SDL_GetModState() & KMOD_CAPS);
    LTBOOL bNumLockOn = KMOD_NUM == (SDL_GetModState() & KMOD_NUM);
    LTBOOL bUpperCase = (bCapsLockOn && !bShiftDown) || (!bCapsLockOn && bShiftDown);

	if (nKey >= 'A' && nKey <= 'Z' && !bUpperCase)
	{
		nKey += 32;
	}
	else if ((nKey >= 48 && nKey <= 57) && bShiftDown)
	{
		// we are not checking explicitly for some of
		// the values included in the ranges above since
		// because they are characters only derived with
		// a shift combination, they should not ever be
		// encountered

		switch (nKey)
		{
			case '0': nKey = ')'; break;
			case '1': nKey = '!'; break;
			case '2': nKey = '@'; break;
			case '3': nKey = '#'; break;
			case '4': nKey = '$'; break;
			case '5': nKey = '%'; break;
			case '6': nKey = '^'; break;
			case '7': nKey = '&'; break;
			case '8': nKey = '*'; break;
			case '9': nKey = '('; break;
		}
	}
	else if ((nKey >= 186 && nKey <= 191) || (nKey >= 219 && nKey <= 222))
	{
		switch (nKey)
		{
			case 186: nKey = bShiftDown ? ':' : ';'; break;
			case 187: nKey = bShiftDown ? '+' : '='; break;
			case 188: nKey = bShiftDown ? '<' : ','; break;
			case 189: nKey = bShiftDown ? '_' : '-'; break;
			case 190: nKey = bShiftDown ? '>' : '.'; break;
			case 191: nKey = bShiftDown ? '?' : '/'; break;

			case 219: nKey = bShiftDown ? '{' : '['; break;
			case 220: nKey = bShiftDown ? '|' : '\\'; break;
			case 221: nKey = bShiftDown ? '}' : ']'; break;
			case 222: nKey = bShiftDown ? '\"' : '\''; break;
		}
	}
	else if (nKey >= 96 && nKey <= 105 && bNumLockOn)
	{
		switch (nKey)
		{
			case SDLK_KP_0: nKey = '0'; break;
			case SDLK_KP_1: nKey = '1'; break;
			case SDLK_KP_2: nKey = '2'; break;
			case SDLK_KP_3: nKey = '3'; break;
			case SDLK_KP_4: nKey = '4'; break;
			case SDLK_KP_5: nKey = '5'; break;
			case SDLK_KP_6: nKey = '6'; break;
			case SDLK_KP_7: nKey = '7'; break;
			case SDLK_KP_8: nKey = '8'; break;
			case SDLK_KP_9: nKey = '9'; break;
		}
	}
	else if (nKey >= 106 && nKey <= 111)
	{
		switch (nKey)
		{
			case SDLK_KP_MULTIPLY:	nKey = '*'; break;
			case SDLK_KP_PLUS:		nKey = '+'; break;
			case SDLK_KP_MINUS:		nKey = '-'; break;
			case SDLK_KP_DECIMAL:	nKey = '.'; break;
			case SDLK_KP_DIVIDE:	nKey = '/'; break;
		}
	}

	return nKey;
}