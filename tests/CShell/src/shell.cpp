#include "ltbasedefs.h"

#include "iclientshell.h"
#include "iltclient.h"

#include <GL/gl.h>
#include <vector>

class MyShell : public IClientShellStub
{
    bool QuitSent=false;
    SDL_Renderer *_ren=nullptr;
    SDL_GLContext _glcx=0;
    SDL_Window *_win=nullptr;
    std::vector<uint> frame_time;
    float ani = -0.55f;
    bool shrink = true;
public:
    declare_interface(MyShell)
    MyShell() = default;
    ~MyShell();
    LTRESULT OnEngineInitialized(RMode *mode, LTGUID *pAppGuid);
    void HandleEvent(SDL_Event e);
    void Update();
private:
    void sdlQuit();
};

define_interface(MyShell, IClientShell)
SETUP_GPLTCLIENT()

LTRESULT
MyShell::OnEngineInitialized(RMode *mode, LTGUID *appID)
{
    frame_time.reserve(30000);
    g_pLTClient->GetEngineHook("SDL_Window", (void**)&_win);
    SDL_SetWindowSize(_win, mode->m_Width, mode->m_Height);
    SDL_SetWindowDisplayMode(_win,nullptr);
    _ren = SDL_GetRenderer(_win);
    if(!_ren) {
        _ren = SDL_CreateRenderer(_win, -1, 0);
    }
    _glcx = SDL_GL_CreateContext(_win);
    return LT_OK;
}

void
MyShell::HandleEvent(SDL_Event e)
{
    if(!QuitSent && e.type == SDL_KEYUP &&
    (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE || e.key.keysym.scancode == SDL_SCANCODE_Q )) {
        sdlQuit();
    }
}

#include <iostream>
void
MyShell::sdlQuit()
{
    if(!QuitSent) {
        SDL_Event quit{};
        quit.type = SDL_QUIT;
        quit.quit.timestamp = SDL_GetTicks();
        SDL_PushEvent(&quit);
        QuitSent = true;
        std::cout << "should be Quitting soon...\n";
    }
}

#include <numeric>
void
MyShell::Update()
{
    auto start = SDL_GetTicks();
    if(_glcx) {
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
            glColor4f(0.5,0.5,1.0,1.0);
            glVertex3f(ani,ani,0.1);
            glVertex3f(0.0, 0.5,0.1);
            glVertex3f(0.5,-0.5,0.1);
        glEnd();
        SDL_GL_SwapWindow(_win);
    } else {
        SDL_SetRenderDrawColor(_ren,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(_ren);
        SDL_Rect rc;
        SDL_RenderGetViewport(_ren, &rc);
        SDL_SetRenderDrawColor(_ren, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawLine(_ren, 320, 200, 300, 240);
        SDL_RenderDrawLine(_ren, 300, 240, 340, 240);
        SDL_RenderDrawLine(_ren, 340, 240, 320, 200);

        SDL_RenderPresent(_ren);
    }
    frame_time.push_back( SDL_GetTicks() - start);
    if (shrink) {
        ani += frame_time.back() * 0.00065f;
        if (ani > -0.45f)
            shrink = !shrink;
    } else {
        ani -= frame_time.back() * 0.00065f;
        if (ani < -0.55f)
            shrink = !shrink;
    }
    if (frame_time.size() > 29500) {
        auto total = std::accumulate(frame_time.begin(),frame_time.end(), 0.0f);
        auto fpt = 1.0f / (total / frame_time.size());
        std::cout << "frames per Tick: " << fpt << "\n - " << start << "\n - " << total << '\n';
        sdlQuit();
    }
}

MyShell::~MyShell()
{
    if(_glcx)
      SDL_GL_DeleteContext(_glcx);
}
