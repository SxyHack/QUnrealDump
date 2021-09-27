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
// 扫描操作, 可以指定多个类型，比如一次扫描包括整数，字符串和浮点。
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
	// 开关
	bool EnableRegionCode = false;    // 是否扫描代码页
	bool EnableRegionMapped = false;  // 是否扫描MEM_MAPPED

protected:
	SWhatList    _WhatList;
	SFindHow*    _How;
	SFindMethod* _Method;
	QSemaphore   _Interrupt;
};
