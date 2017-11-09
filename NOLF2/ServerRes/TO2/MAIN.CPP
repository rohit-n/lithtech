#ifdef _WIN32
#include <windows.h>

extern "C"
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID )
{
    return 1;
}
#endif