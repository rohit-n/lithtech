#include "bdefs.h"
#include "timemgr.h"
#include "clientmgr.h"

#include <unistd.h>
#include <iostream>
#include <SDL_syswm.h>

//holder for command line argument mgr interface.
#include "icommandlineargs.h"
static ICommandLineArgs *command_line_args;
define_holder(ICommandLineArgs, command_line_args);

extern char g_SSFile[];
extern LTBOOL g_bNullRender;
extern int32 g_CV_CursorCenter;
extern int32 g_nConsoleLines;
extern LTBOOL g_bConsoleEnable;
extern int32 g_bShowRunningTime;
extern LTBOOL g_CV_HighPriority;
extern int32 g_CV_PlayDemoReps;
extern int32 g_CV_NoDefaultEngineRez;

int32 g_CurRunIteration=0;

ClientGlob g_ClientGlob;
uint32 g_EngineStartMS;

int RunClientApp()
{
    //should set AllocHook here, maybe?

    ClientGlob  *pGlob = &g_ClientGlob;
    memset(pGlob, 0, sizeof(*pGlob));
	pGlob->m_bConsoleEnabled = true;
    pGlob->m_bInputEnabled = true;

    if (command_line_args->FindArgDash("DebugStructBanks")) {
        g_bDebugStructBanks = LTTRUE;
    }

    const char *pArg = command_line_args->FindArgDash("workingdir");
    // if chdir fails it returns non-zero making the expression true
    if (pArg && chdir(pArg)) {
        return -1;
    }

    int status = dsi_Init();
    if(status != 0) {
        if(status == 1) {
            std::cout << "ERROR: unable to load ltmsg\n";
        } else {
            std::cout << "ERROR: unable to initialize LithTech Engine\n";
        }
        dsi_Term();
        return -1;
    }

    // initialize ClientMgr
    cm_Init();
    pGlob->m_bClientActive = true;

    pGlob->m_WndCaption = command_line_args->FindArgDash("windowtitle");
    if(pGlob->m_WndCaption == nullptr){
        pGlob->m_WndCaption = "LithTech";
    }

    pGlob->m_bBreakOnError = command_line_args->FindArgDash("breakonerror") != NULL;
	SDL_Init(SDL_INIT_EVERYTHING);
	pGlob->m_window = SDL_CreateWindow(pGlob->m_WndCaption, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
	SDL_SysWMinfo info;
	SDL_VERSION(&info.version);
	SDL_GetWindowWMInfo(pGlob->m_window, &info);


    return 0;
}

bool SetupArgs(int argc, char *argv[])
{
    command_line_args->Init(argc, argv);

    return true;
}

int main(int p1, char *p2[])
{
    LTMemInit();

    g_EngineStartMS = timeGetTime();
    if(! SetupArgs(p1, p2) )
    {
        return -1;
    }
    int ret = RunClientApp();
    if (g_CV_PlayDemoReps > 1)
    {
        g_CurRunIteration++;
        while(g_CV_PlayDemoReps > g_CurRunIteration)
        {
            g_CurRunIteration++;
            ret = RunClientApp();      
        }

    }

    return ret;
}