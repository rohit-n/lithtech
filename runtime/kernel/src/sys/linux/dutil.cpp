#include "bdefs.h"
#include "dutil.h"

bool du_UpperStrcmp(const char *str1, const char *str2)
{
    return (ci_string{str1} == ci_string{str2});
}