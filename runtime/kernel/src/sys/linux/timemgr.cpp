
#include "timemgr.h"
#include <SDL.h>

float time_GetTime()
{
    return (float)(timeGetTime()) / 1000.0f;
}

uint32 timeGetTime()
{
	return SDL_GetTicks();
}
