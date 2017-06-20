#include "bdefs.h"
#include "input.h"
#include "dsys_interface.h"
#include "dinput.h"
#include <SDL.h>
#include "sdl2_scancode_to_dinput.h"

#define SPECIAL_MOUSEX	-50000
#define SPECIAL_MOUSEY	-50001
#define SPECIAL_MOUSECLICK_LEFT	 -50002
#define SPECIAL_MOUSECLICK_RIGHT -50003

struct SDL2Key
{
	char *m_pName;
	SDL_Keycode key;
	float m_Scale;
};

struct ISAction
{
	char m_Name[100];
	int m_Code;
	ISAction *m_pNext;
};

struct ISBinding
{
	char m_deviceName[32];
	float m_ranges[2];
	SDL2Key *m_pKey;
	ISAction *m_pAction;
	ISBinding *m_pNext;
};


ISBinding *g_Bindings_sdl2;
ISAction *g_Actions_sdl2;

SDL2Key g_Keys[] =
{
	"X-axis", SPECIAL_MOUSEX, 1.0f,
	"Y-axis", SPECIAL_MOUSEY, 1.0f,

	"Button 0", SPECIAL_MOUSECLICK_LEFT, 1.0f,
	"Button 1", SPECIAL_MOUSECLICK_RIGHT, 1.0f,

	"Left Alt", SDLK_LALT,  1.0f,
	"Right Alt", SDLK_RALT, 1.0f,

	"A", SDLK_a, 1.0f,
	"B", SDLK_b, 1.0f,
	"C", SDLK_c, 1.0f,
	"D", SDLK_d, 1.0f,
	"E", SDLK_e, 1.0f,
	"F", SDLK_f, 1.0f,
	"G", SDLK_g, 1.0f,
	"H", SDLK_h, 1.0f,
	"I", SDLK_i, 1.0f,
	"J", SDLK_j, 1.0f,
	"K", SDLK_k, 1.0f,
	"L", SDLK_l, 1.0f,
	"M", SDLK_m, 1.0f,
	"N", SDLK_n, 1.0f,
	"O", SDLK_o, 1.0f,
	"P", SDLK_p, 1.0f,
	"Q", SDLK_q, 1.0f,
	"R", SDLK_r, 1.0f,
	"S", SDLK_s, 1.0f,
	"T", SDLK_t, 1.0f,
	"U", SDLK_u, 1.0f,
	"V", SDLK_v, 1.0f,
	"W", SDLK_w, 1.0f,
	"X", SDLK_x, 1.0f,
	"Y", SDLK_y, 1.0f,
	"Z", SDLK_z, 1.0f,

	"1", SDLK_1, 1.0f,
	"2", SDLK_2, 1.0f,
	"3", SDLK_3, 1.0f,
	"4", SDLK_4, 1.0f,
	"5", SDLK_5, 1.0f,
	"6", SDLK_6, 1.0f,
	"7", SDLK_7, 1.0f,
	"8", SDLK_8, 1.0f,
	"9", SDLK_9, 1.0f,
	"0", SDLK_0, 1.0f,

	"F1", SDLK_F1, 1.0f,
	"F2", SDLK_F2, 1.0f,
	"F3", SDLK_F3, 1.0f,
	"F4", SDLK_F4, 1.0f,
	"F5", SDLK_F5, 1.0f,
	"F6", SDLK_F6, 1.0f,
	"F7", SDLK_F7, 1.0f,
	"F8", SDLK_F8, 1.0f,
	"F9", SDLK_F9, 1.0f,
	"F10", SDLK_F10, 1.0f,
	"F11", SDLK_F11, 1.0f,
	"F12", SDLK_F12, 1.0f,

	// "Numpad 1", VK_NUMPAD1, DIK_NUMPAD1, 1.0f,
	// "Numpad 2", VK_NUMPAD2, DIK_NUMPAD2, 1.0f,
	// "Numpad 3", VK_NUMPAD3, DIK_NUMPAD3, 1.0f,
	// "Numpad 4", VK_NUMPAD4, DIK_NUMPAD4, 1.0f,
	// "Numpad 5", VK_NUMPAD5, DIK_NUMPAD5, 1.0f,
	// "Numpad 6", VK_NUMPAD6, DIK_NUMPAD6, 1.0f,
	// "Numpad 7", VK_NUMPAD7, DIK_NUMPAD7, 1.0f,
	// "Numpad 8", VK_NUMPAD8, DIK_NUMPAD8, 1.0f,
	// "Numpad 9", VK_NUMPAD9, DIK_NUMPAD9, 1.0f,
	// "Numpad +", VK_ADD, DIK_ADD, 1.0f,
	// "Numpad -", VK_SUBTRACT, DIK_SUBTRACT, 1.0f,
	// "Numpad *", VK_MULTIPLY, DIK_MULTIPLY, 1.0f,
	// "Numpad /", VK_DIVIDE, DIK_DIVIDE, 1.0f,

	"Up Arrow", SDLK_UP, 1.0f,
	"Left Arrow", SDLK_LEFT, 1.0f,
	"Down Arrow", SDLK_DOWN, 1.0f,
	"Right Arrow", SDLK_RIGHT, 1.0f,
	// "PgUp", VK_PRIOR, DIK_PRIOR, 1.0f,
	// "PgDn", VK_NEXT, DIK_NEXT, 1.0f,
	// "Home", VK_HOME, DIK_HOME, 1.0f,
	// "End", VK_END, DIK_END, 1.0f,

	"Backspace", SDLK_BACKSPACE, 1.0f,
	"Tab", SDLK_TAB, 1.0f,
	"Enter", SDLK_RETURN, 1.0f,
	"Left Ctrl", SDLK_LCTRL, 1.0f,
	"Right Ctrl", SDLK_RCTRL, 1.0f,
	"Left Shift", SDLK_LSHIFT, 1.0f,
	"Right Shift", SDLK_RSHIFT, 1.0f,
	"Space", SDLK_SPACE, 1.0f,
	"CapsLock", SDLK_CAPSLOCK, 1.0f
};
#define NUM_KEYS (sizeof(g_Keys)/sizeof(g_Keys[0]))

static int SDLScanCodeToKeyNum(SDL_Scancode sc)
{
	int idx = (int)sc;
	ASSERT(idx >= 0 && idx < SDL_NUM_SCANCODES);
	return scanCodeToKeyNum[idx];
}

SDL2Key* input_sdl2_FindKey(const char *pName, const char* deviceName)
{
	uint32 i;
	int testCode;
	int dik;
	SDL_Scancode scancode;

	if(strlen(pName) > 2 && pName[0] == '#' && pName[1] == '#')
	{
		pName += 2;

		if(stricmp(pName, "x-axis") == 0)
		{
			return &g_Keys[0];
		}
		if(stricmp(pName, "y-axis") == 0)
		{
			return &g_Keys[1];
		}
		if(!strcmp(pName, "3") && !strcmp(deviceName, "##mouse"))
		{
			return &g_Keys[2];
		}
		if(!strcmp(pName, "4") && !strcmp(deviceName, "##mouse"))
		{
			return &g_Keys[3];
		}

		testCode = atoi(pName);
		for(i=0; i < NUM_KEYS; i++)
		{
			scancode = SDL_GetScancodeFromKey(g_Keys[i].key);
			dik = SDLScanCodeToKeyNum(scancode);

			if(dik == testCode)
			{
				return &g_Keys[i];
			}
		}

		// Fall below where it looks without the ##.
	}

	for(i=0; i < NUM_KEYS; i++)
	{
		if(stricmp(pName, g_Keys[i].m_pName) == 0)
		{
			return &g_Keys[i];
		}
	}

	return LTNULL;
}

ISAction* input_sdl2_FindAction(const char *pName)
{
	ISAction *pCur;

	for(pCur=g_Actions_sdl2; pCur; pCur=pCur->m_pNext)
	{
		if(stricmp(pCur->m_Name, pName) == 0)
			return pCur;
	}

	return LTNULL;
}


bool input_sdl2_init(InputMgr *pMgr, ConsoleState *pState)
{
	g_Bindings_sdl2 = LTNULL;
	g_Actions_sdl2 = LTNULL;
	return true;
}

void input_sdl2_term(InputMgr *pMgr)
{
	ISBinding *pBinding, *pNextBinding;
	ISAction *pAction, *pNextAction;

	for(pBinding=g_Bindings_sdl2; pBinding; )
	{
		pNextBinding = pBinding->m_pNext;
		dfree(pBinding);
		pBinding = pNextBinding;
	}
	g_Bindings_sdl2 = LTNULL;

	for(pAction=g_Actions_sdl2; pAction; )
	{
		pNextAction = pAction->m_pNext;
		dfree(pAction);
		pAction = pNextAction;
	}
	g_Actions_sdl2 = LTNULL;
}

bool input_sdl2_IsInitted(InputMgr *pMgr)
{
	return true;
}

void input_sdl2_ListDevices(InputMgr *pMgr)
{
	dsi_ConsolePrint("SIMULATED INPUT ------------------");
	dsi_ConsolePrint("Only devices are keyboard and mouse");
}

long input_sdl2_PlayJoystickEffect(InputMgr *pMgr, const char* strEffectName, float x, float y)
{
	return 0;
}

void input_sdl2_ReadInput(InputMgr *pMgr, uint8 *pActionsOn, float axisOffsets[3], void* keyDowns, int* mouseclick, int* mouserel)
{
	ISBinding *pBinding;
	float value;
	POINT cursorPos;
	int mx, my, i;
	SDL_Keycode* downs = (SDL_Keycode*)keyDowns;
	SDL_Scancode scancode;

	axisOffsets[0] = axisOffsets[1] = axisOffsets[2] = 0.0f;

	for(pBinding=g_Bindings_sdl2; pBinding; pBinding=pBinding->m_pNext)
	{
		value = 0.0f;

		if(pBinding->m_pKey->key == SPECIAL_MOUSEX)
		{
			value = (float)(mouserel[0]) * pBinding->m_pKey->m_Scale;
		}
		else if(pBinding->m_pKey->key == SPECIAL_MOUSEY)
		{
			value = (float)(mouserel[1]) * pBinding->m_pKey->m_Scale;
		}
		else if(pBinding->m_pKey->key == SPECIAL_MOUSECLICK_LEFT && mouseclick[0])
		{
			value = 1.0f;
		}
		else if(pBinding->m_pKey->key == SPECIAL_MOUSECLICK_RIGHT && mouseclick[1])
		{
			value = 1.0f;
		}
		else
		{
			scancode = SDL_GetScancodeFromKey(pBinding->m_pKey->key);
			if(downs[scancode] == 1)
			{
				value = 1.0f;
			}
		}

		switch(pBinding->m_pAction->m_Code)
		{
		case -1:
			{
				axisOffsets[0] += value;
			}
			break;

		case -2:
			{
				axisOffsets[1] += value;
			}
			break;

		case -3:
			{
				axisOffsets[2] += value;
			}
			break;

		default:
			{
				pActionsOn[pBinding->m_pAction->m_Code] |= (uint8)value;
			}
			break;
		}
	}
}

bool input_sdl2_FlushInputBuffers(InputMgr *pMgr)
{
	return true;
}

LTRESULT input_sdl2_ClearInput()
{
	return LT_OK;
}

void input_sdl2_AddAction(InputMgr *pMgr, const char *pActionName, int actionCode)
{
	ISAction *pAction = input_sdl2_FindAction(pActionName);

	if(pAction)
		return;

	LT_MEM_TRACK_ALLOC(pAction = (ISAction*)dalloc(sizeof(ISAction)),LT_MEM_TYPE_INPUT);
	LTStrCpy(pAction->m_Name, pActionName, sizeof(pAction->m_Name));
	pAction->m_Code = actionCode;
	pAction->m_pNext = g_Actions_sdl2;
	g_Actions_sdl2 = pAction;
}

bool input_sdl2_EnableDevice(InputMgr *pMgr, const char *pDeviceName)
{
	return true;
}

bool input_sdl2_ClearBindings(InputMgr *pMgr, const char *pDeviceName, const char *pTriggerName)
{
	return true;
}

bool input_sdl2_AddBinding(InputMgr *pMgr,
	const char *pDeviceName, const char *pTriggerName, const char *pActionName,
	float rangeLow, float rangeHigh)
{
	ISBinding *pBinding;
	if (strlen(pDeviceName) == 0)
	{
		return false;
	}

	ISAction *pAction = input_sdl2_FindAction(pActionName);
	if(!pAction)
		return false;

	SDL2Key *pKey = input_sdl2_FindKey(pTriggerName, pDeviceName);
	if(!pKey)
		return false;

	LT_MEM_TRACK_ALLOC(pBinding = (ISBinding*)dalloc(sizeof(ISBinding)),LT_MEM_TYPE_INPUT);
	pBinding->m_pKey = pKey;
	pBinding->m_pAction = pAction;
	pBinding->m_pNext = g_Bindings_sdl2;
	strcpy(pBinding->m_deviceName, pDeviceName);
	pBinding->m_ranges[0] = rangeLow;
	pBinding->m_ranges[1] = rangeHigh;

	g_Bindings_sdl2 = pBinding;
	return true;
}

bool input_sdl2_ScaleTrigger(InputMgr *pMgr, const char *pDeviceName, const char *pTriggerName, float scale, float fRangeScaleMin, float fRangeScaleMax, float fRangeScalePreCenterOffset )
{
	SDL2Key *pKey = input_sdl2_FindKey(pTriggerName, pDeviceName);

	if(pKey)
	{
		pKey->m_Scale = scale;
		return true;
	}
	else
	{
		return false;
	}
}

DeviceBinding* input_sdl2_GetDeviceBindings ( uint32 nDevice )
{
	DeviceBinding* pBindingsHead = LTNULL;
	ISBinding *pISBinding;

	pISBinding = g_Bindings_sdl2;
	while(pISBinding)
	{
		DeviceBinding* pBinding;
		LT_MEM_TRACK_ALLOC(pBinding = new DeviceBinding,LT_MEM_TYPE_INPUT);
		if( !pBinding ) break;
		memset( pBinding, 0, sizeof(DeviceBinding) );

		LTStrCpy( pBinding->strDeviceName, "Keyboard", sizeof(pBinding->strDeviceName) );
		LTStrCpy( pBinding->strTriggerName, pISBinding->m_pKey->m_pName, sizeof(pBinding->strTriggerName) );

		// go through the actions, adding them to the trigger
		GameAction* pActionHead = LTNULL;

		GameAction* pNewAction;
		LT_MEM_TRACK_ALLOC(pNewAction = new GameAction,LT_MEM_TYPE_INPUT);
		memset( pNewAction, 0, sizeof(GameAction) );

		pNewAction->nActionCode = pISBinding->m_pAction->m_Code;
		strcpy (pNewAction->strActionName, pISBinding->m_pAction->m_Name);
		pNewAction->pNext = pActionHead;
		pActionHead = pNewAction;

		pBinding->pActionHead = pActionHead;

		pBinding->pNext = pBindingsHead;
		pBindingsHead = pBinding;

		pISBinding = pISBinding->m_pNext;
	}

	return pBindingsHead;
}

void input_sdl2_SaveBindings(FILE *fp)
{
	ISAction* action_cur;
	ISBinding* bind_cur;
	SDL_Scancode scancode;
	int dik;
	int i;
	char* axis;

	for(action_cur=g_Actions_sdl2; action_cur; action_cur=action_cur->m_pNext)
	{
		fprintf(fp, "AddAction %s %d\n", action_cur->m_Name, action_cur->m_Code);
	}

	fprintf(fp, "\nenabledevice \"##keyboard\"\n");
	for(bind_cur=g_Bindings_sdl2; bind_cur; bind_cur=bind_cur->m_pNext)
	{
		scancode = SDL_GetScancodeFromKey(bind_cur->m_pKey->key);
		dik = SDLScanCodeToKeyNum(scancode);
		if (!strcmp(bind_cur->m_deviceName, "##keyboard"))
		{
			fprintf(fp, "rangebind \"##keyboard\" \"##%d\" %f %f \"%s\"\n",
				dik, bind_cur->m_ranges[0], bind_cur->m_ranges[1], bind_cur->m_pAction->m_Name);
		}
	}

	fprintf(fp, "\nenabledevice \"##mouse\"\n");
	for(bind_cur=g_Bindings_sdl2; bind_cur; bind_cur=bind_cur->m_pNext)
	{
		scancode = SDL_GetScancodeFromKey(bind_cur->m_pKey->key);
		dik = SDLScanCodeToKeyNum(scancode);
		axis = NULL;
		if (strcmp(bind_cur->m_deviceName, "##mouse"))
		{
			continue;
		}

		if (!strcmp(bind_cur->m_pAction->m_Name, "Axis1"))
		{
			axis = "x-axis";
		}
		else if (!strcmp(bind_cur->m_pAction->m_Name, "Axis2"))
		{
			axis = "y-axis";
		}
		else
		{
			/* other action */
			if (bind_cur->m_pKey->key == SPECIAL_MOUSECLICK_LEFT)
			{
				axis = "3";
			}
			if (bind_cur->m_pKey->key == SPECIAL_MOUSECLICK_RIGHT)
			{
				axis = "4";
			}
		}

		if (axis == NULL)
		{
			continue;
		}
		fprintf(fp, "rangebind \"##mouse\" \"##%s\" %f %f \"%s\"\n",
			axis, bind_cur->m_ranges[0], bind_cur->m_ranges[1], bind_cur->m_pAction->m_Name);
	}

	for(i = 0; i < NUM_KEYS; i++)
	{
		if(!stricmp(g_Keys[i].m_pName, "x-axis"))
		{
			fprintf(fp, "scale \"##mouse\" \"##x-axis\" %f\n", g_Keys[i].m_Scale);
		}
		if(!stricmp(g_Keys[i].m_pName, "y-axis"))
		{
			fprintf(fp, "scale \"##mouse\" \"##y-axis\" %f\n", g_Keys[i].m_Scale);
		}
	}
}

void input_sdl2_FreeDeviceBindings ( DeviceBinding* pBindings )
{
	DeviceBinding* pBinding = pBindings;
	while( pBinding )
	{
		GameAction* pAction = pBinding->pActionHead;
		while( pAction )
		{
			GameAction* pNext = pAction->pNext;
			delete pAction;
			pAction = pNext;
		}

		DeviceBinding* pNext = pBinding->pNext;
		delete pBinding;
		pBinding = pNext;
	}
}

bool input_sdl2_StartDeviceTrack(InputMgr *pMgr, uint32 nDeviceFlags, uint32 nBufferSize)
{
	return true;
}

bool input_sdl2_TrackDevice(DeviceInput *pInputArray, uint32 *pnInOut)
{
	*pnInOut = 0;
	return true;
}

bool input_sdl2_EndDeviceTrack()
{
	return true;
}

DeviceObject* input_sdl2_GetDeviceObjects ( uint32 nDeviceFlags )
{
	return LTNULL;
}

void input_sdl2_FreeDeviceObjects ( DeviceObject* pList )
{
}

bool input_sdl2_GetDeviceName ( uint32 nDeviceType, char* pStrBuffer, uint32 nBufferSize )
{
	return true;
}

bool input_sdl2_IsDeviceEnabled ( const char* pDeviceName )
{
	return true;
}

static bool input_sdl2_GetDeviceObjectName( char const* pszDeviceName, uint32 nDeviceObjectId,
	char* pszDeviceObjectName, uint32 nDeviceObjectNameLen )
{
	return true;
}

InputMgr g_InputSDL2Mgr =
{
	input_sdl2_init,
	input_sdl2_term,
	input_sdl2_IsInitted,
	input_sdl2_ListDevices,
	input_sdl2_PlayJoystickEffect,
	input_sdl2_ReadInput,
	input_sdl2_FlushInputBuffers,
	input_sdl2_ClearInput,
	input_sdl2_AddAction,
	input_sdl2_EnableDevice,
	input_sdl2_ClearBindings,
	input_sdl2_AddBinding,
	input_sdl2_ScaleTrigger,
	input_sdl2_GetDeviceBindings,
	input_sdl2_FreeDeviceBindings,
	input_sdl2_StartDeviceTrack,
	input_sdl2_TrackDevice,
	input_sdl2_EndDeviceTrack,
	input_sdl2_GetDeviceObjects,
	input_sdl2_FreeDeviceObjects,
	input_sdl2_GetDeviceName,
	input_sdl2_GetDeviceObjectName,
	input_sdl2_IsDeviceEnabled
};