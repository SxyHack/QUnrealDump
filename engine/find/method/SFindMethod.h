#pragma once

#include <QThread>
#include <QSemaphore>
#include <windows.h>

class SOptScanning;

//
// ��ô��
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

	// �ж��Ƿ��Ǵ���ҳ(.text)
	virtual bool IsCodeRegion(const MEMORY_BASIC_INFORMATION& mbi);

protected:
	SOptScanning* _Operation;
	QSemaphore    _Stop;
};
