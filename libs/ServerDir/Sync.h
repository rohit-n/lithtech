//////////////////////////////////////////////////////////////////////////////
// Selecting System-specific synchronization object wrapping classes

#ifndef __SYNC_H__
#define __SYNC_H__

#ifdef __LINUX
#include "LinSync.h"
typedef LinSync_CS Sync_CS;
typedef LinSync_CSAuto Sync_CSAuto;
typedef LinSync_Event Sync_Event;
typedef LinSync_PulseEvent Sync_PulseEvent;
#else
#include "WinSync.h"
typedef CWinSync_CS Sync_CS;
typedef CWinSync_CSAuto Sync_CSAuto;
typedef CWinSync_Event Sync_Event;
typedef CWinSync_PulseEvent Sync_PulseEvent;
#endif

#endif