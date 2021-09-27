#pragma once

#include <QRunnable>
#include <QQueue>

class SFindMethodFast;
class SOptScanning;
class SFindWhat;
//
// 
//
class SFastWorker : public QRunnable
{
public:
	SFastWorker(quint64 nBegAddr, quint64 nEndAddr, SFindMethodFast* pMethod, SFindWhat* pWhat);
	~SFastWorker();

	void run() override;

protected:
	SFindMethodFast* _Method;
	SOptScanning*    _Operation;
	SFindWhat*       _What;
	quint64          _BegAddr;
	quint64          _EndAddr;
};

typedef QQueue<SFastWorker*> SFastWorkerQueue;
