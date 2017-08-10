#include "bdefs.h"
#include "input.h"

extern InputMgr g_InputSDL2Mgr;
LTRESULT input_GetManager(InputMgr **pMgr)
{
    *pMgr = &g_InputSDL2Mgr;
    return LT_OK;
}
