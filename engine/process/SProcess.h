#pragma once

#include "global.h"

class SProcess
{
protected:
	SProcess();
	~SProcess();

public:
	static SProcess& Get();

public:
	//
	// 打开进程
	//
	BOOL Open(quint64 nPID);
	BOOL NtOpen(quint64 nPID);
	BOOL IsOpen();
	void Close();

	// 
	// 初始化内存访问器
	// [IN] bInternal 传True代表启动注入式, 传False代表为外挂式
	// 
	void SetupAccessor(bool bInternal = true);

	bool ReadInt8(quint64 nAddress, quint8& value);
	bool ReadInt16(quint64 nAddress, quint16& value);
	bool ReadInt32(quint64 nAddress, quint32& value);
	bool ReadInt64(quint64 nAddress, quint64& value);
	bool ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer);

	//
	// 返回进程句柄
	//
	HANDLE GetHandle();

	quint64 GetNumberOfProcessor();
	quint64 GetBegAddress();
	quint64 GetEndAddress();
	quint64 GetSize();
};


#define GProcess SProcess::Get()
