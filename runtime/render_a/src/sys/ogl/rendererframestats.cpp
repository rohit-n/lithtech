#include "ltbasedefs.h"
#include "ogl_render.h"

#include "rendererframestats.h"

int    GetFrameStats(LTRendererStats &refStats)
{
    return 0;
}

int
OGLRenderer::getFrameStats(LTRendererStats &stats)
{
    return GetFrameStats(stats);
}
