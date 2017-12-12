#include "ltbasedefs.h"

#include "iclientshell.h"
class MyShell : public IClientShell
{
    const char* _InterfaceImplementation() {return "AlchemyTest";};
};

MyShell shell;

