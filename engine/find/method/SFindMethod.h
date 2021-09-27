#pragma once

#include <QThread>
#include <QSemaphore>
#include <windows.h>

class SOptScanning;

//
// 怎么找
//
class SFindMethod : public QThread
{
	Q_OBJECT

public:
	SFindMethod();
	~SFindMethod();

	void SetOptScanning(SOptScanning* pOperation);
	SOptScanning* GetOptScanning();

	virtual void Start();
	virtual void Stop();

	virtual bool IsValidRegion(const MEMORY_BASIC_INFORMATION& mbi);
	//
	// 判断内存页是否是代码
	//
	virtual bool IsCodeRegion(const MEMORY_BASIC_INFORMATION& mbi);

protected:
	SOptScanning* _Operation;
	QSemaphore    _Stop;
};
