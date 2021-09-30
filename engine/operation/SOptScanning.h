#pragma once

#include "SOperation.h"
#include "SFindWhat.h"
#include "SFindHow.h"
#include "SFindMethod.h"
#include <QList>
#include <QSemaphore>
#include <QTime>


//
// 扫描操作, 可以指定多个类型，比如一次扫描包括整数，字符串和浮点。
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


	SFindHow* GetHow();
	SWhatList& GetWhatList();

	void OutputDebugElapse();

public:
	// 开关
	bool EnableRegionCode = true;    // 是否扫描代码页

	bool EnableRegionMapped = false;  // 是否扫描MEM_MAPPED
	bool EnableRegionPrivate = true;
	bool EnableRegionImage = true;

protected:
	SWhatList     _WhatList;
	SFindHow*     _How;
	SFindMethod*  _Method;
	QSemaphore    _Interrupt;
	QElapsedTimer _Time;
};
