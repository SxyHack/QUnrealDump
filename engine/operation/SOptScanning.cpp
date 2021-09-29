#include "SOptScanning.h"
#include "SFindWhat.h"
#include "SFindHow.h"
#include "SFindMethodFast.h"

SOptScanning::SOptScanning(SFindMethod* pMethod, SFindWhat* pWhat, SFindHow* pHow)
	: SOperation(NULL)
	, _How(pHow)
	, _Method(pMethod)
{
	pWhat->SetRoot(this);
	_How->SetOptScanning(this);
	_Method->SetOptScanning(this);

	_WhatList.append(pWhat);
}

SOptScanning::SOptScanning(SFindMethod* pMethod, SWhatList whats, SFindHow* pHow)
	: SOperation(NULL)
	, _WhatList(whats)
	, _How(pHow)
	, _Method(pMethod)
{
	for (auto pWhat : _WhatList)
	{
		pWhat->SetRoot(this);
	}

	_How->SetOptScanning(this);
	_Method->SetOptScanning(this);
}

SOptScanning::~SOptScanning()
{
}

void SOptScanning::Start()
{
	_Method->start(QThread::HighestPriority);
}

void SOptScanning::Stop()
{
	_Method->Stop();
	_Interrupt.release(); // +1
}

bool SOptScanning::IsStopped()
{
	return _Interrupt.tryAcquire();
}

SFindHow* SOptScanning::GetHow()
{
	return _How;
}

SWhatList& SOptScanning::GetWhatList()
{
	return _WhatList;
}
