#include <dlfcn.h>
#include <cstring>
#include <cinttypes>

typedef const char* (*resString)(uint32_t);

uint32_t LoadString(void *h, int id, char* buff, int len)
{
    auto s = (resString*)dlsym(h, "LoadString");
    const char *tmp =  (*s)(id);
    std::strncpy(buff, tmp, len);
    return std::strlen(buff);
}
