#include "ltbasedefs.h"

#include "iclientshell.h"
class MyShell : public IClientShellStub
{
public:
    declare_interface(MyShell)
    MyShell() = default;
};

define_interface(MyShell, IClientShell)
