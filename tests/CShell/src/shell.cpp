#include "ltbasedefs.h"

#include "iclientshell.h"
class MyShell : public IClientShellStub
{
    bool QuitSent=false;
    SDL_Renderer *_ren=nullptr;
public:
    declare_interface(MyShell)
    MyShell() = default;
    LTRESULT OnEngineInitialized(RMode *mode, LTGUID *pAppGuid);
    void HandleEvent(SDL_Event e);
    void Update();
};

define_interface(MyShell, IClientShell)


LTRESULT
MyShell::OnEngineInitialized(RMode *mode, LTGUID *appID)
{
    SDL_Window *win = SDL_GetGrabbedWindow();
    SDL_SetWindowSize(win, mode->m_Width, mode->m_Height);
    SDL_SetWindowDisplayMode(win,nullptr);
    _ren = SDL_GetRenderer(win);
    if(!_ren) {
        _ren = SDL_CreateRenderer(win, -1, 0);
    }
    return LT_OK;
}

#include <iostream>
void
MyShell::HandleEvent(SDL_Event e)
{
    if(!QuitSent && e.type == SDL_KEYUP && 
    (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE || e.key.keysym.scancode == SDL_SCANCODE_Q )) {
        SDL_Event quit{};
        quit.type = SDL_QUIT;
        quit.quit.timestamp = SDL_GetTicks();
        SDL_PushEvent(&quit);
        QuitSent = true;
        std::cout << "should be Quitting soon...\n";
    }
}

void
MyShell::Update()
{
    SDL_SetRenderDrawColor(_ren,0,0,0,255);
    SDL_RenderClear(_ren);
    SDL_RenderPresent(_ren);
}
