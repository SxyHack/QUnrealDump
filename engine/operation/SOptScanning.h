#pragma once

#include "SOperation.h"
#include "SFindWhat.h"
#include "SFindHow.h"
#include "SFindMethod.h"
#include <QList>
#include <QSemaphore>

//class SFindMethod;
//class SFindHow;


//
// ɨ�����, ����ָ��������ͣ�����һ��ɨ������������ַ����͸��㡣
//
class SOptScanning : public SOperation
{
public:
	SOptScanning(SFindWhat* pWhat, SFindHow* pHow, SFindMethod* pMethod);
	SOptScanning(SWhatList whats, SFindHow* pHow, SFindMethod* pMethod);
	~SOptScanning();

	void Start() override;
	void Stop() override;
	bool IsStopped() override;


	SFindHow* GetHow();
	SWhatList& GetWhatList();

public:
	// ����
	bool EnableRegionCode = false;    // �Ƿ�ɨ�����ҳ
	bool EnableRegionMapped = false;  // �Ƿ�ɨ��MEM_MAPPED

protected:
	SWhatList    _WhatList;
	SFindHow*    _How;
	SFindMethod* _Method;
	QSemaphore   _Interrupt;
};
