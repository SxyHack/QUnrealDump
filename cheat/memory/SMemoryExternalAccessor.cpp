#include "SMemoryExternalAccessor.h"
#include "SProcess.h"

SMemoryExternalAccessor::SMemoryExternalAccessor()
	: _Buffer(nullptr)
	, _BufferSize(0)
{
}

SMemoryExternalAccessor::~SMemoryExternalAccessor()
{
	if (_Buffer)
	{
		delete[] _Buffer;
	}
}

quint8 SMemoryExternalAccessor::ReadInt8(quint64 nAddress)
{
	return *(quint8*)Read(nAddress, sizeof(quint8));
}

quint16 SMemoryExternalAccessor::ReadInt16(quint64 nAddress)
{
	return *(quint16*)Read(nAddress, sizeof(quint16));
}

quint32 SMemoryExternalAccessor::ReadInt32(quint64 nAddress)
{
	return *(quint32*)Read(nAddress, sizeof(quint32));
}

quint64 SMemoryExternalAccessor::ReadInt64(quint64 nAddress)
{
	return *(quint64*)Read(nAddress, sizeof(quint64));
}

quint8* SMemoryExternalAccessor::Read(quint64 nAddress, qint32 nSize)
{
	SIZE_T nReadedSize = 0;
	HANDLE hProcess = GProcess.GetHandle();
	LPVOID pAddress = (LPVOID)(GProcess.GetBaseAddress() + nAddress);

	if (hProcess == NULL)
	{
		qCritical("Read 0x%x:0x%x size:%d Failed, not open process", nAddress, pAddress, nSize);
		return nullptr;
	}

	if (_Buffer == nullptr)
	{
		_BufferSize = nSize;
		_Buffer = new char[nSize];
		ZeroMemory(_Buffer, nSize);
	}
	else
	{
		if (nSize > _BufferSize) // 如果新的大小比老的大小更大，则重新申请内存。
		{
			delete[] _Buffer;
			_Buffer = new char[nSize];
			_BufferSize = nSize;
		}

		ZeroMemory(_Buffer, nSize);
	}

	if (!::ReadProcessMemory(hProcess, pAddress, _Buffer, nSize, &nReadedSize))
	{
		qWarning("Read 0x%x:0x%x size:%d Failed.", nAddress, pAddress, nSize);
		return nullptr;
	}

	qInfo("Read 0x%x:0x%x size:%d Okay.", nAddress, pAddress, nSize);
	return (quint8*)_Buffer;
}
