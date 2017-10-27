//////////////////////////////////////////////////////////////////////////////
// Linux-specific synchronization object wrapping classes

#ifndef __LINSYNC_H__
#define __LINSYNC_H__

#include <pthread.h>
struct evt_mutex {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    bool trigger;
};
typedef pthread_mutex_t CRITICAL_SECTION;
typedef evt_mutex* HANDLE;
typedef void* HMODULE;

#define _stdcall

// Critical section
class LinSync_CS
{
public:
	LinSync_CS() {
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&GetCS(), &attr);
	}
	~LinSync_CS() {
		pthread_mutex_destroy(&GetCS());
	}

	void Enter() {
		pthread_mutex_lock(&GetCS());
	}

	void Leave() {
		pthread_mutex_unlock(&GetCS());
	}

	CRITICAL_SECTION &GetCS() const { return m_CS; }

private:
	mutable pthread_mutex_t m_CS;
};

// Auto enter/leave wrapper for a critical section based on variable scope
class LinSync_CSAuto
{
public:
	LinSync_CSAuto(const LinSync_CS &cCS) : m_pCS(&cCS.GetCS())
	{
		pthread_mutex_lock(m_pCS);
	}
	LinSync_CSAuto(CRITICAL_SECTION *pCS) : m_pCS(pCS)
	{
		pthread_mutex_lock(m_pCS);
	}
	~LinSync_CSAuto()
	{
		pthread_mutex_unlock(m_pCS);
	}

private:
	mutable pthread_mutex_t *m_pCS;
};

// Event
class LinSync_Event
{
public:
	LinSync_Event() {
        pthread_mutex_init(&m_hEvent.mutex,0);
        pthread_cond_init(&m_hEvent.cond,0);
        m_hEvent.trigger = false;
	}
	~LinSync_Event() {
        pthread_mutex_destroy(&m_hEvent.mutex);
		pthread_cond_destroy(&m_hEvent.cond);
	}
	HANDLE GetEvent() const { return &m_hEvent; }
	void Set() {
        pthread_mutex_lock(&m_hEvent.mutex);
        m_hEvent.trigger = true;
        pthread_cond_signal(&m_hEvent.cond);
        pthread_mutex_unlock(&m_hEvent.mutex);
    }
	bool Clear() {
        pthread_mutex_lock(&m_hEvent.mutex);
        m_hEvent.trigger = false;
        pthread_mutex_lock(&m_hEvent.mutex);
        return true;
    }
	bool IsSet() const { return m_hEvent.trigger; }
	bool Block(uint32_t nTimeout = 0xffffffffL) {
        HANDLE ev = GetEvent();
        if(nTimeout != 0xffffffffL){
                // should use timedwait here
        }
        pthread_mutex_lock(&ev->mutex);
        while (!ev->trigger)
            pthread_cond_wait(&ev->cond, &ev->mutex);
        pthread_mutex_unlock(&ev->mutex);
        return true;
    }
protected:
	void SetEvent(HANDLE hEvent) { m_hEvent = *hEvent; }
private:
    evt_mutex m_hEvent;
};

// Event which resets after releasing a block
class LinSync_PulseEvent : public LinSync_Event
{
public:
	LinSync_PulseEvent() :LinSync_Event{} {
        Set();
	}
};

// stubs for bloody Windows API

uint32_t WaitForMultipleObjects(uint32_t count, const HANDLE* objs, bool flag, uint32_t timeout){return 0;}
void WaitForSingleObject(const HANDLE obj,uint32_t timeout){}
HANDLE CreateThread(void* t, int, uint32_t (*func)(void*), void *cl, int, uintptr_t*id)
{
    id=0;
    return nullptr;
}

void CloseHandle(HANDLE hdl){}

uint32_t LoadString(HMODULE mod, uint32_t msgCode,char* buff, size_t len)
{
    return 0;
}

#define WAIT_OBJECT_0 0
#define WAIT_TIMEOUT 0xffffffffL

#endif
