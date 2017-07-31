#include "bdefs.h"
#include "input.h"

LTRESULT input_GetManager(InputMgr **pMgr)
{
    static InputMgr mgr{};
    *pMgr = &mgr;
    return LT_OK;
}