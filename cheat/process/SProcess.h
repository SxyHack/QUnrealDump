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
	// �򿪽���
	//
	BOOL Open(quint64 nPID);
	BOOL NtOpen(quint64 nPID);

	//
	// ���ؽ��̾��
	//
	HANDLE GetHandle();

	// 
	// ���ؽ��̻���ַ��exeģ��Ļ���ַ
	//
	quint64 GetBaseAddress();
};


#define GProcess SProcess::Get()
