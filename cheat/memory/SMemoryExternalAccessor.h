#pragma once

#include "SMemoryAccessor.h"

class SMemoryExternalAccessor : public SMemoryAccessor
{
public:
	SMemoryExternalAccessor();
	~SMemoryExternalAccessor();

	quint8  ReadInt8(quint64 nAddress) override;
	quint16 ReadInt16(quint64 nAddress) override;
	quint32 ReadInt32(quint64 nAddress) override;
	quint64 ReadInt64(quint64 nAddress) override;

private:
	quint8* Read(quint64 nAddress, qint32 nSize);

protected:
	char*  _Buffer;
	qint32 _BufferSize;
};
