// ----------------------------------------------------------------------- //
//
// MODULE  : AssertMgr.cpp
//
// PURPOSE : AssertMgr implementation
//
// CREATED : 05.06.1999
//
// ----------------------------------------------------------------------- //

#include <SDL.h>

#include "StdAfx.h"
#include "AssertMgr.h"
// Statics

LTBOOL CAssertMgr::m_bEnabled = LTFALSE;
_CRT_REPORT_HOOK CAssertMgr::m_crhPrevious = LTNULL;

#ifdef __LINUX
#include <vector>

int
MessageBox(SDL_Window *win, std::string message, std::string title, uint32 flags)
{
	std::vector<SDL_MessageBoxButtonData> btns{};
    if ((flags & MB_ASSERT) > 0) {
		btns.emplace_back(SDL_MessageBoxButtonData{0,IDABORT,"Abort"});
		btns.emplace_back(SDL_MessageBoxButtonData{0,IDRETRY,"Retry"});
		btns.emplace_back(SDL_MessageBoxButtonData{0,IDIGNORE,"Ignore"});
	} else if((flags & MB_OKCANCEL)) {
		btns.emplace_back(SDL_MessageBoxButtonData{0,IDOK,"Ok"});
		btns.emplace_back(SDL_MessageBoxButtonData{0,IDCANCEL,"Cancel"});
	}

    const SDL_MessageBoxColorScheme colors = {
        { 
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
	const SDL_MessageBoxData mbox_data = {
		SDL_MESSAGEBOX_WARNING,
		win,
		title.c_str(),
		message.c_str(),
		SDL_arraysize(btns.data()),
		btns.data(),
		&colors
	};
    int button = MBOX_ERROR;
	SDL_ShowMessageBox(&mbox_data, &button);
	return button;
}

#endif

// Methods

void CAssertMgr::Enable()
{
#ifdef _DEBUG
    if ( LTTRUE == m_bEnabled ) return;

    m_bEnabled = LTTRUE;
	m_crhPrevious = _CrtSetReportHook(CAssertMgr::ReportHook);
#endif
}

void CAssertMgr::Disable()
{
#ifdef _DEBUG
    if ( LTFALSE == m_bEnabled ) return;

	_CrtSetReportHook(m_crhPrevious);

    m_bEnabled = LTFALSE;
    m_crhPrevious = LTNULL;
#endif
}

int CAssertMgr::CreateMessageBox(SDL_Window *win, const char *szMsg)
{
	const SDL_MessageBoxButtonData btns[] = {
		{0,IDABORT,"Abort"},
		{0,IDRETRY,"Retry"},
		{0,IDIGNORE,"Ignore"}
	};
    const SDL_MessageBoxColorScheme colors = {
        { 
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
	if(win)
		SDL_MinimizeWindow(win);
	const SDL_MessageBoxData mbox_data = {
		SDL_MESSAGEBOX_WARNING,
		win,
		"Assert",
		szMsg,
		SDL_arraysize(btns),
		btns,
		&colors
	};
	int button=15;
	SDL_ShowMessageBox(&mbox_data, &button);
	return button;

}

int CAssertMgr::ReportHook(int nReportType, const char* szMessage, int* pnReturnValue)
{
    if ( LTFALSE == m_bEnabled )
	{
		*pnReturnValue = 0;
		return 0;
	}

	const char* szAssert = NULL;

#ifdef _CLIENTBUILD
	HCONSOLEVAR hAssertVar;
    hAssertVar = g_pLTClient->GetConsoleVar("assert");
	if ( hAssertVar )
	{
        szAssert = g_pLTClient->GetVarValueString(hAssertVar);
	}
#else
	HCONVAR hAssertVar;
    hAssertVar = g_pLTServer->GetGameConVar("assert");
	if (!hAssertVar)
	{
        g_pLTServer->SetGameConVar("assert", "console");
        hAssertVar = g_pLTServer->GetGameConVar("assert");
	}
    szAssert = g_pLTServer->GetVarValueString(hAssertVar);
#endif

	if ( szAssert && !stricmp(szAssert, "fullscreen") )
	{
		// if assert convar = "fullscreen", switch out of renderer then do abort, retry, ignore

		char szBuffer[512];
		sprintf(szBuffer, "\
An assert has occurred:\n\n%s\n\
Retry will step into the debugger. You should\n\
only select this option if you are currently\n\
running the game under a debugger.\n", szMessage);

		SDL_Window *win = SDL_GetGrabbedWindow();

		int nResult = CreateMessageBox(win, szBuffer);

		if ( nResult == IDABORT )
		{
			*pnReturnValue = 0;
		}
		else if ( nResult == IDRETRY )
		{
			*pnReturnValue = 1;
		}
		else // if ( nResult == IDIGNORE )
		{
			if(win)
				SDL_MaximizeWindow(win);
			*pnReturnValue = 0;
		}

		return TRUE;
	}
	else if ( szAssert && !stricmp(szAssert, "window") )
	{
		// if assert convar = "window", then do as normal (usually a dialog)

		char szBuffer[512];
		sprintf(szBuffer, "\
An assert has occurred:\n\n%s\n\
Retry will step into the debugger. You should\n\
only select this option if you are currently\n\
running the game under a debugger.\n", szMessage);

		SDL_Window *win = SDL_GetGrabbedWindow();

		int nResult = CreateMessageBox(win, szBuffer);

		if ( nResult == IDABORT )
		{
			*pnReturnValue = 0;
		}
		else if ( nResult == IDRETRY )
		{
			*pnReturnValue = 1;
		}
		else // if ( nResult == IDIGNORE )
		{
			*pnReturnValue = 0;
		}

		return TRUE;
	}
	else if ( szAssert && !stricmp(szAssert, "null") )
	{
		// if assert convar = "null", then totally ignore it

		*pnReturnValue = 0;
		return TRUE;
	}
	else // if ( !stricmp(szAssert, "console") )
	{
		// if assert convar = "console" or none of the above, put the assert into the console

#ifdef _CLIENTBUILD
        g_pLTClient->CPrint(szMessage);
#else
        g_pLTServer->CPrint(szMessage);
#endif
		*pnReturnValue = 0;
		return TRUE;
	}
}