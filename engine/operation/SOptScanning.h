#pragma once

#include "SOperation.h"
#include "SFindWhat.h"
#include "SFindHow.h"
#include "SFindMethod.h"
#include <QList>
#include <QSemaphore>
#include <QTime>


//
// ɨ�����, ����ָ��������ͣ�����һ��ɨ������������ַ����͸��㡣
//
class SOptScanning : public SOperation
{
public:
	SOptScanning(SFindMethod* pMethod, SFindWhat* pWhat, SFindHow* pHow);
	SOptScanning(SFindMethod* pMethod, SWhatList whats, SFindHow* pHow);
	~SOptScanning();

	void Start() override;
	void Stop() override;
	bool IsStopped() override;
	bool WaitForDone() override;

	SFindHow* GetHow();
	SWhatList& GetWhatList();
	quint64 GetFirstAddress();

	void OutputDebugElapse();

signals:
	void sFound(quint64 nAddress);

public:
	// ����
	bool EnableRegionCode = true;    // �Ƿ�ɨ�����ҳ

	bool EnableRegionMapped = false;  // �Ƿ�ɨ��MEM_MAPPED
	bool EnableRegionPrivate = true;
	bool EnableRegionImage = true;

	quint64 AddressOfSignature; // ɨ��������ʹ��

protected:
	SWhatList     _WhatList;
	SFindHow*     _How;
	SFindMethod*  _Method;
	QSemaphore    _Interrupt;
	QElapsedTimer _Time;
	quint64       _Address;
};
