#ifndef __VIDEOMGR_H__
#define __VIDEOMGR_H__

#include "ltbasedefs.h"


class VideoInst {
protected:
    virtual ~VideoInst() = default;
public:
    virtual LTRESULT DrawVideo();  // Stub RKJ
    virtual int  GetVideoStatus(); // Stub RKJ
    virtual LTRESULT Update();
    virtual void Release();   // Stub RKJ
};


class VideoMgr {
protected:
    virtual ~VideoMgr() = default;
public:
    virtual void OnRenderInit();
    virtual void UpdateVideos();
    virtual bool CreateScreenVideo(const char *,uint32, VideoInst*);
    CMultiLinkList<VideoInst*> m_Videos;
};


extern VideoMgr* CreateVideoMgr(const char *pName);
#endif
