#pragma once

#include "SMemoryAccessor.h"

class SMemoryInternalAccessor : public SMemoryAccessor
{
public:
	SMemoryInternalAccessor();
	~SMemoryInternalAccessor();

	quint8  ReadInt8(quint64 nAddress) override;
	quint16 ReadInt16(quint64 nAddress) override;
	quint32 ReadInt32(quint64 nAddress) override;
	quint64 ReadInt64(quint64 nAddress) override;
};
