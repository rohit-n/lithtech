#include <dlfcn.h>
#include <cstring>

typedef const char* (resString*)(uint32_t);

void LoadString(void *h, int id, char* buff, int len)
{
    auto s = (resString*)dlsym(h, "LoadString");
    const char *tmp =  (*s)(id);
    std::strncpy(buff, tmp, len);
}