#include <iostream>
#include "resources.h"
#include "dynres.h"
#include <dlfcn.h>

void printString(int id, void *resdll)
{
    char buffer[512] = {'\0'};
    LoadString(resdll, id, buffer, 500);
    std::cout << buffer << '\n';
}

int main(int, char**)
{
    std::cout << "loading strings from sharable object\n";
    void *h = dlopen("./libCRes.so", RTLD_NOW);
    if(h != nullptr) {
        printString(IDS_VERSION, h);
        printString(IDS_APPNAME, h);
        dlclose(h);
    }
    return 0;
}