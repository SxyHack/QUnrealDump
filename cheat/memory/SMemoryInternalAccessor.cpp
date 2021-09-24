#include "SMemoryInternalAccessor.h"

SMemoryInternalAccessor::SMemoryInternalAccessor()
	: SMemoryAccessor()
{
}

SMemoryInternalAccessor::~SMemoryInternalAccessor()
{
}

quint8 SMemoryInternalAccessor::ReadInt8(quint64 nAddress)
{
	return *(quint8*)nAddress;
}

quint16 SMemoryInternalAccessor::ReadInt16(quint64 nAddress)
{
	return *(quint16*)nAddress;
}

quint32 SMemoryInternalAccessor::ReadInt32(quint64 nAddress)
{
	return *(quint32*)nAddress;
}

quint64 SMemoryInternalAccessor::ReadInt64(quint64 nAddress)
{
	return *(quint64*)nAddress;
}
