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
	// 返回进程句柄
	//
	HANDLE GetHandle();
};


#define GProcess SProcess::Get()
