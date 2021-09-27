#include "SMemoryInternalAccessor.h"

SMemoryInternalAccessor::SMemoryInternalAccessor()
	: SMemoryAccessor()
{
}

SMemoryInternalAccessor::~SMemoryInternalAccessor()
{
}

bool SMemoryInternalAccessor::ReadInt8(quint64 nAddress, quint8& value)
{
	value = *(quint8*)nAddress;
	return true;
}

bool SMemoryInternalAccessor::ReadInt16(quint64 nAddress, quint16& value)
{
	value = *(quint16*)nAddress;
	return true;
}

bool SMemoryInternalAccessor::ReadInt32(quint64 nAddress, quint32& value)
{
	value = *(quint32*)nAddress;
	return true;
}

bool SMemoryInternalAccessor::ReadInt64(quint64 nAddress, quint64& value)
{
	value = *(quint64*)nAddress;
	return true;
}

bool SMemoryInternalAccessor::ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer)
{
	*pBuffer = (quint8*)nAddress;
	return true;
}
