#pragma once

#include "SMemoryAccessor.h"

class SMemoryInternalAccessor : public SMemoryAccessor
{
public:
	SMemoryInternalAccessor();
	~SMemoryInternalAccessor();

	bool ReadInt8(quint64 nAddress, quint8& value) override;
	bool ReadInt16(quint64 nAddress, quint16& value) override;
	bool ReadInt32(quint64 nAddress, quint32& value) override;
	bool ReadInt64(quint64 nAddress, quint64& value) override;
	bool ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer) override;
};
