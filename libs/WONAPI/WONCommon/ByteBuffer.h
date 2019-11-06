#ifndef __WON_BYTEBUFFER_H__
#define __WON_BYTEBUFFER_H__
#include "WONShared.h"

#include <string>
#include <assert.h>
#include "SmartPtr.h"

namespace WONAPI
{

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
class ByteBuffer : public WONAPI::RefCount
{
private:
	char *mData;
	unsigned long mDataLen;

public:
	ByteBuffer();
	ByteBuffer(const void *theData, unsigned long theLen, bool takeOwnership=false);
	explicit ByteBuffer(const char *theStr);

	const char* data() const { return mData; }
	unsigned long length() const { return mDataLen; }

protected:
	virtual ~ByteBuffer();
};

typedef ConstSmartPtr<ByteBuffer> ByteBufferPtr;

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

}; // namespace WONAPI

#endif
