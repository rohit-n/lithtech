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

bool testSetKeyNumber()
{
    std::cout << "starting set number key\n";
    {
        CRegMgr mgr;
        mgr.Init("Alchemiestick", "MyTestApplication", "1.0");
        mgr.Set("dpi", 96);
    } // need to be sure it's stored between sessions
    CRegMgr mgr;
    mgr.Init("Alchemiestick", "MyTestApplication", "1.0");
    return (mgr.Get("dpi",0) == 96);
}

#include <vector>
#include <string>

template<typename B>
std::vector<std::basic_string<B>> split(const std::basic_string<B> &src, B sep);

void printList(const std::vector<std::string> &a)
{
    for (auto &&v : a)
        std::cout << '\'' << v << "'\n";
}

bool testSplitString()
{
    std::cout << "starting split string test\n";
    { // empty string
        std::string empty{};
        auto a{split(empty, ' ')};
        std::cout << "vector size of empty: " << a.size() << '\n';
        if(a.size() != 0)
            return false;
        printList(a);
    }    
    { // string w/ 1 character
        std::string one{"1"};
        auto a{split(one, ' ')};
        std::cout << "vector size of one: " << a.size() << '\n';
        if(a.size() != 1)
            return false;
        printList(a);
        }    
    { // string w/ 3 character and no splitting character 
        std::string three{"123"};
        auto a{split(three, ' ')};
        std::cout << "vector size of three: " << a.size() << '\n';
        if(a.size() != 1)
            return false;
        printList(a);
    }    
    { // string w/ 3 character and with a separator
        std::string three{"1 3"};
        auto a{split(three, ' ')};
        std::cout << "vector size of three /w sep: " << a.size() << '\n';
        if(a.size() != 2)
            return false;
        printList(a);
    }    
    { // string w/ 4 character and with two separator
        std::string three{"1 3 "};
        auto a{split(three, ' ')};
        std::cout << "vector size of three /w sep: " << a.size() << '\n';
        if(a.size() != 3)
            return false;
        printList(a);
    }    
    { // complicated string
        std::string msg{"hello world! May the force be with you."};
        auto a{split(msg, ' ')};
        std::cout << "vector size of complex /w sep: " << a.size() << '\n';
        if(a.size() != 8)
            return false;
        printList(a);
    }    
    return true;
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
    if(! testSplitString())
        return 1;
    std::cout << "splitString template pass\n";
    if(! testGetVersionInt() )
        return 1;
    if(! testGetVersionStr() )
        return 1;
    std::cout << "Get version Pass\n";
    if(! testSetVersionStr() )
        return 1;
    std::cout << "Set version Pass\n";
    if(! testSetKeyNumber() )
       return 1;
    std::cout << "Set numeric key Pass\n";
    return 0;
}
