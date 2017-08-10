#include "bdefs.h"
#include "input.h"

void in_Term(InputMgr*)
{
}

LTRESULT input_GetManager(InputMgr **pMgr)
{
    static InputMgr mgr{};
    mgr.Term = &in_Term;
    *pMgr = &mgr;
    return LT_OK;
}
