#include "bdefs.h"
#include "timemgr.h"

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