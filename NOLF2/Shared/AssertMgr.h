// ----------------------------------------------------------------------- //
//
// MODULE  : AssertMgr.h
//
// PURPOSE : AssertMgr definition
//
// CREATED : 05.06.1999
//
// ----------------------------------------------------------------------- //

#ifndef __ASSERT_MGR_H__
#define __ASSERT_MGR_H__

#include <SDL.h>

#ifdef __LINUX
typedef void* _CRT_REPORT_HOOK;
#define IDABORT 0
#define IDRETRY 1
#define IDIGNORE 2
#define IDOK 3
#define IDCANCEL 4
#define MBOX_ERROR 15

#define MB_ASSERT 1
#define MB_OKCANCEL 2

#include <string>

int MessageBox(SDL_Window *win, std::string message, std::string title, uint32 buttonflag);

#endif


class CAssertMgr
{
	public : // Public methods

		static void Enable();
		static void Disable();

	protected : // Protected methods

		static int ReportHook(int nReportType, const char* szMessage, int* pnReturnValue);
		static int CreateMessageBox(SDL_Window *win, const char *szMsg);

	protected : // Protected member variables

        static LTBOOL            m_bEnabled;
		static _CRT_REPORT_HOOK	m_crhPrevious;
};

#endif