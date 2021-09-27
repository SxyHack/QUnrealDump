#pragma once

#include "SMemoryAccessor.h"
#include "SProcess.h"

class SMemoryExternalAccessor : public SMemoryAccessor
{
public:
	SMemoryExternalAccessor();
	~SMemoryExternalAccessor();

	bool ReadInt8(quint64 nAddress, quint8& value) override;
	bool ReadInt16(quint64 nAddress, quint16& value) override;
	bool ReadInt32(quint64 nAddress, quint32& value) override;
	bool ReadInt64(quint64 nAddress, quint64& value) override;
	bool ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer) override;

protected:
	template<class T>
	bool Read(quint64 nAddress, T& value)
	{
		SIZE_T nReadedSize = 0;
		LPVOID pAddress = (LPVOID)nAddress;
		HANDLE hProcess = GProcess.GetHandle();
		qint32 nSize = sizeof(T);
		if (hProcess == NULL)
		{
			qCritical("Read 0x%X:%d Failed, not open process", nAddress, nSize);
			return false;
		}

		if (!::ReadProcessMemory(hProcess, pAddress, (LPVOID)&value, nSize, &nReadedSize))
		{
			qCritical("Read 0x%X:%d Failed.", nAddress, nSize);
			return false;
		}

		qDebug("Read 0x%X:%d Okay.", nAddress, nSize);
		return true;
	}
};
