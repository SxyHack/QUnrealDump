#include "SMemoryExternalAccessor.h"
#include "SProcess.h"

SMemoryExternalAccessor::SMemoryExternalAccessor()
{
}

SMemoryExternalAccessor::~SMemoryExternalAccessor()
{
}

bool SMemoryExternalAccessor::ReadInt8(quint64 nAddress, quint8& value)
{
	return Read<quint8>(nAddress, value);
}

bool SMemoryExternalAccessor::ReadInt16(quint64 nAddress, quint16& value)
{
	return Read<quint16>(nAddress, value);
}

bool SMemoryExternalAccessor::ReadInt32(quint64 nAddress, quint32& value)
{
	return Read<quint32>(nAddress, value);
}

bool SMemoryExternalAccessor::ReadInt64(quint64 nAddress, quint64& value)
{
	return Read<quint64>(nAddress, value);
}

bool SMemoryExternalAccessor::ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer)
{
	SIZE_T nReadedSize = 0;
	LPVOID pAddress = (LPVOID)nAddress;
	HANDLE hProcess = GProcess.GetHandle();
	if (hProcess == NULL)
	{
		qCritical("Read 0x%X:%d Failed, not open process", nAddress, nSize);
		return false;
	}

	if (!::ReadProcessMemory(hProcess, pAddress, (LPVOID)*pBuffer, nSize, &nReadedSize))
	{
		qCritical("Read 0x%X:%d Failed.", nAddress, nSize);
		return false;
	}

	//qDebug("Read 0x%X:%d Okay.", nAddress, nSize);
	return true;
}
