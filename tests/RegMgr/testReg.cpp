#include <iostream>
#include "regmgr.h"

bool testInit()
{
    CRegMgr mgr;
    return mgr.Init("Alchemiestick", "MyTestApplication", "1.0");
}

bool testGetVersionInt()
{
    CRegMgr mgr;
    mgr.Init("Alchemiestick", "MyTestApplication", "1.0");
    DWORD x = 4;
    DWORD y = mgr.Get("version", x);
    std::cout << y << '\n';
    if ( y != x )
        return false;
    return true;
}

bool testGetVersionStr()
{
    CRegMgr mgr;
    mgr.Init("Alchemiestick", "MyTestApplication", "1.0");
    char ver[5];
    uint32_t len = sizeof(ver);
    ver[0] = '\0';
    mgr.Get("version", ver, len,"0.0");
    std::cout << ver << '\n';
    if ( std::string{ver} == std::string{"1.0"} )
        return true;
    return false;
}

int main()
{
    // I can init the "registry" as many times as I want
    for(int i=0;i<4;i++)
        if(! testInit() )
        {
            std::cout << "init failed\n";
            return 1;
        }
    std::cout << "init Pass\n";
    if(! testGetVersionInt() )
        return 1;
    if(! testGetVersionStr() )
        return 1;
    std::cout << "version Pass\n";
    return 0;
}
