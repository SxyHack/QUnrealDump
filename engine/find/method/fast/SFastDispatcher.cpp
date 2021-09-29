#include "SFastDispatcher.h"
#include "SFindMethodFast.h"

SFastDispatcher::SFastDispatcher(SFindMethodFast* pMethod)
	: QThread()
	, _Method(pMethod)
{
}

SFastDispatcher::~SFastDispatcher()
{
}

void SFastDispatcher::run()
{
	while (!isInterruptionRequested())
	{
		if (_Queue.isEmpty())
		{
			//qDebug("Fast Dispatch Queue Is Empty");
			//_IdleSPH.acquire();
			QThread::msleep(10);
			continue;
		}

		SFastWorker* pWorker = _Queue.first();
		_Method->StartWorker(pWorker);

		//_MutexOfQueue.lock();
		_Queue.removeFirst();
		//_MutexOfQueue.unlock();
	}
}

void SFastDispatcher::PushQueue(SFastWorker* pWorker)
{
	_Queue.push_back(pWorker);
	//_IdleSPH.release();
}

void SFastDispatcher::Stop()
{
	requestInterruption();
	qDebug("Stopping...");
	wait();
	qInfo("STOPPED");
}
