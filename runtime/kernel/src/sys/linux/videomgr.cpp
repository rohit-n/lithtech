#include "bdefs.h"
#include "videomgr.h"

LTRESULT VideoInst::DrawVideo()
{
    return LT_OK;
}
int VideoInst::GetVideoStatus()
{
    return 0;
}
void VideoInst::Release() {}

bool VideoMgr::CreateScreenVideo(const char *,uint32, VideoInst*) 
{
    return true;
}

void VideoMgr::OnRenderInit() {}

void VideoMgr::UpdateVideos() {}

VideoMgr* CreateVideoMgr(const char *pName) {
    return new VideoMgr();
}