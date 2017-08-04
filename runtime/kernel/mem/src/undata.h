// ------------------------------------------------------------------------- //
//
// FILE      : U N D A T A . H
//
// CREATED   : 10/29/99
//
// AUTHOR    : Matthew Scott
//
// COPYRIGHT : Monolith Productions Inc.
//
// ORIGN     : Loosly based upon struct banks and moArray's
//
// ------------------------------------------------------------------------- //

#ifndef __UNDATA_H__
#define __UNDATA_H__

// ------------------------------------------------------------------------- //
// Includes this module depends on
// ------------------------------------------------------------------------- //
#include "ltbasetypes.h"
#include "stdlterror.h"
#include "ltassert.h"

// ------------------------------------------------------------------------- //
// Typedefs
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Externs (Public C data)
// ------------------------------------------------------------------------- //
extern class CGenUnboundData *g_pUnboundData;

// ------------------------------------------------------------------------- //
// Prototypes (Public C methods)
// ------------------------------------------------------------------------- //

// ------------------------------------------------------------------------- //
// Class Definitions
// ------------------------------------------------------------------------- //

class CGenUnboundData {
	// The heap
	uintptr_t* heapStart;
	uintptr_t* heapEnd;

	// The free list
	uintptr_t* FreeListHead;
	uint32 minFreeBlocks;
	uint32 CurBlockSize;
	uint32 FreeBlocks;
	uint32 GetCnt;
	uint32 RetCnt;

	public:
		// Set it all up called from derived class constructor
		ESTDLTResults Init();

		uint32  GetBlockSize    ();

		// get and return of memory blocks
		uintptr_t* GetNewBlock     ();
		void   ReturnOldBlock  (uintptr_t* block);

		// platform specific routine for seting up initial memory segment
		virtual ESTDLTResults
		initUnboundHeap (uint32 blockSize, uintptr_t** begin, uintptr_t** end) = 0;

		// print debug info
		void PrintUndataStats ();
};

inline uintptr_t*
CGenUnboundData::GetNewBlock () {
	uintptr_t *retVal;

	if (FreeListHead == NULL) {
		ASSERT (false);
		return (NULL);
	}

	FreeBlocks--;
 
	if (FreeBlocks < minFreeBlocks)
		minFreeBlocks = FreeBlocks;
	ASSERT (minFreeBlocks > 0);

	GetCnt++;

	retVal = FreeListHead;
	FreeListHead = (uintptr_t *)(*FreeListHead);
	return (retVal);
}

inline uint32
CGenUnboundData::GetBlockSize () {
	return (CurBlockSize);
}

inline void
CGenUnboundData::ReturnOldBlock (uintptr_t* block) {
	// Error checking
	if (block == NULL) {
		CRITICAL_ERROR ("undata.h", "Tried to free a NULL block");
	}

	// 1st word of block (next pointer) gets what FreeListHead was pointing at
	// if we gave out the last block
	//*block = (FreeListHead == NULL) ? (uint32) NULL : (uint32) *FreeListHead;
	*block = (uintptr_t) FreeListHead;

	FreeListHead = block;
	FreeBlocks++;
	RetCnt++;
}

#endif  // __UNDATA_H__

