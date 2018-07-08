#ifndef __RENDERERFRAMESTATS_H__
#define __RENDERERFRAMESTATS_H__

class LTRendererStats;
int    GetFrameStats(LTRendererStats &refStats);
typedef int    (*GetFrameStatsFn)(LTRendererStats &refStats);

#endif // __RENDERERFRAMESTATS_H__