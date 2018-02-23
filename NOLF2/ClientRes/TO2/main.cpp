#ifdef _WIN32
#include <windows.h>

extern "C"
BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID )
{
    return 1;
}
#else

void __attribute__((constructor)) InitializeResourceSystem() {
    setup_string_tables();
    setup_cursors();
    return;
}

#endif