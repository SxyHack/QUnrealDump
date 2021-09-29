#pragma once

#include <QRunnable>
#include <QList>

#include "SFindWhat.h"

class SFindMethodFast;
class SOptScanning;

//
// 
//
class SFastWorker : public QRunnable
{
public:
	SFastWorker(quint64 nBegAddr, quint64 nEndAddr, SFindMethodFast* pMethod, SWhatList& whats);
	~SFastWorker();

	void run() override;

protected:
	SFindMethodFast* _Method;
	SOptScanning*    _Operation;
	SWhatList        _Whats;
	quint64          _BegAddr;
	quint64          _EndAddr;
};

typedef QList<SFastWorker*> SFastWorkerList;
