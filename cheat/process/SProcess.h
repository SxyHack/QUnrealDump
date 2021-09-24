#pragma once

#include "global.h"

class SProcess
{
public:
	SProcess();
	~SProcess();

	static SProcess& Get();

public:
	//
	// 打开进程
	//
	BOOL Open(quint64 nPID);
	BOOL NtOpen(quint64 nPID);

	//
	// 返回进程句柄
	//
	HANDLE GetHandle();

	// 
	// 返回进程基地址，exe模块的基地址
	//
	quint64 GetBaseAddress();
};


#define GProcess SProcess::Get()
