#include "SFastWorker.h"
#include "SFindMethodFast.h"
#include "SOptScanning.h"
#include "SProcess.h"
#include "SFindHow.h"

SFastWorker::SFastWorker(quint64 nBegAddr, quint64 nEndAddr, SFindMethodFast* pMethod, SFindWhat* pWhat)
	: QRunnable()
	, _Method(pMethod)
	, _Operation(pMethod->GetOptScanning())
	, _What(pWhat)
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

	if (_Operation->IsStopped()) {
		return;
	}

	quint64 nRegionSize = _EndAddr - _BegAddr;
	quint8* pBuffer = new quint8[nRegionSize];
	ZeroMemory(pBuffer, nRegionSize);

	if (!GProcess.ReadBytes(_BegAddr, nRegionSize, &pBuffer))
	{
		goto WORKER_END;
	}

	if (!_What->Lookup(pBuffer, nRegionSize, _Operation->GetHow()))
	{
		goto WORKER_END;
	}

WORKER_END:
	delete[] pBuffer;
}
