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
	// �򿪽���
	//
	BOOL Open(quint64 nPID);
	BOOL NtOpen(quint64 nPID);
	BOOL IsOpen();
	void Close();

	//
	// ���ؽ��̾��
	//
	HANDLE GetHandle();
};


#define GProcess SProcess::Get()
