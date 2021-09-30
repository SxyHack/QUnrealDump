#include "SFastWorker.h"
#include "SFindMethodFast.h"
#include "SOptScanning.h"
#include "SProcess.h"
#include "SFindHow.h"
#include "utility/Elapsed.h"

SFastWorker::SFastWorker(quint64 nBegAddr, quint64 nEndAddr, SFindMethodFast* pMethod, SWhatList& whats)
	: QRunnable()
	, _Method(pMethod)
	, _Operation(pMethod->GetOptScanning())
	, _Whats(whats)
	, _BegAddr(nBegAddr)
	, _EndAddr(nEndAddr)
{
}

SFastWorker::~SFastWorker()
{
}

void SFastWorker::run()
{
	if (_Method->isInterruptionRequested()) {
		return;
	}
	quint64 nRegionSize = _EndAddr - _BegAddr;
	SElapsed elapse(QString("FastWorker:%1").arg(nRegionSize));
	//qDebug("Region:%p - %p", _BegAddr, _EndAddr);

	auto pHow = _Operation->GetHow();

	for (auto pWhat : _Whats) 
	{
		if (_Method->isInterruptionRequested()) {
			return;
		}

		quint8* pBuffer = new quint8[nRegionSize];
		ZeroMemory(pBuffer, nRegionSize);

		if (!GProcess.ReadBytes(_BegAddr, nRegionSize, &pBuffer))
		{
			goto WORKER_END;
		}

		if (!pWhat->Lookup(_BegAddr, pBuffer, nRegionSize, pHow))
		{
			goto WORKER_END;
		}


	WORKER_END:
		delete[] pBuffer;
	}
}