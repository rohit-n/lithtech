#include <cstring>
#include "ltbasedefs.h"
#include "rendererframestats.h"
#include "ltrendererstats.h"
#include "ogl_render.h"


int    GetFrameStats(LTRendererStats &refStats)
{
    memset(&refStats,0,sizeof(LTRendererStats));
    return 0;
}

int
OGLRenderer::getFrameStats(LTRendererStats &stats)
{
    return GetFrameStats(stats);
}
