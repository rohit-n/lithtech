// ------------------------------------------------------------------------- //
//
// FILE      : S Y S D D S T R U C T S . H
//
// CREATED   : 08 / 14 / 00
//
// AUTHOR    : 
//
// COPYRIGHT : Monolith Productions Inc.
//
// ------------------------------------------------------------------------- //

#ifndef __SYSDDSTRUCTS_H__
#define __SYSDDSTRUCTS_H__

// This is a redirector to get the system dependent include
#if defined(__LINUX) && !defined(USE_DXVK)
#include "sys/linux/linuxddstructs.h"
#else
#include "sys/win/d3dddstructs.h"
#endif


#endif

