#pragma once

#include <QThread>
#include <QMutex>
#include <QSemaphore>

#include "SFastWorker.h"

class SFindMethodFast;

//
//
//
class SFastDispatcher : public QThread
{
	Q_OBJECT

public:
	SFastDispatcher(SFindMethodFast* pMethod);
	~SFastDispatcher();

	void run() override;

	//
	// Push Worker Into Queue
	//
	void PushQueue(SFastWorker* pWorker);
	void Stop();

protected:
	SFindMethodFast* _Method;
	SFastWorkerQueue _Queue;
	QMutex           _MutexOfQueue;
	QSemaphore       _IdleSPH;
};
