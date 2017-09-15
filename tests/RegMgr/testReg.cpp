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

bool validateVersion(CRegMgr &mgr, std::string const& test)
{
    char ver[5];
    uint32_t len = sizeof(ver);
    ver[0] = '\0';
    mgr.Get("version", ver, len,"0.0");
    std::cout << ver << '\n';
    return ( test == std::string{ver} );

}

bool testGetVersionStr()
{
    CRegMgr mgr;
    std::string ver{"1.0"};
    mgr.Init("Alchemiestick", "MyTestApplication", ver.c_str());
    return validateVersion(mgr, ver);
}


bool testSetVersionStr()
{
    CRegMgr mgr;
    mgr.Init("Alchemiestick", "MyTestApplication", "1.0");
    std::string ver{"1.1"};
    mgr.Set("version",ver.c_str());
    return validateVersion(mgr, ver);
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
    std::cout << "Get version Pass\n";
    if(! testSetVersionStr() )
        return 1;
    std::cout << "Set version Pass\n";
return 0;
}
