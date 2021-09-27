#pragma once

#include "SFindMethod.h"
#include "SFastDispatcher.h"
#include <QThreadPool>

class SFastWorker;

//
//
//
class SFindMethodFast : public SFindMethod
{
	Q_OBJECT

public:
	SFindMethodFast();
	~SFindMethodFast();

	void StartWorker(SFastWorker* pWorker);
	void Stop() override;

protected:
	void run() override;

private:
	QThreadPool     _ThreadPool;
	SFastDispatcher _Dispatcher;
};
