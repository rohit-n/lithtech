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
LTRESULT VideoInst::Update()
{
    return LT_OK;
}
void VideoInst::Release(){}

bool VideoMgr::CreateScreenVideo(const char *,uint32, VideoInst*&) 
{
    return true;
}

void VideoMgr::OnRenderInit() {}

void VideoMgr::UpdateVideos() 
{
    uint32 running=0;

    for(MPOS pos=m_Videos; pos;)
    {
        VideoInst *pVideo = m_Videos.GetNext(pos);
        pVideo->Update();
        if(pVideo->GetVideoStatus() != 0)
            ++running;
    }
}

VideoMgr* CreateVideoMgr(const char *pName) {
    return new VideoMgr();
}