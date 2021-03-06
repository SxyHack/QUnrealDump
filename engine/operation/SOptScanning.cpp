#include "SOptScanning.h"
#include "SFindWhat.h"
#include "SFindHow.h"
#include "SFindMethodFast.h"

SOptScanning::SOptScanning(SFindMethod* pMethod, SFindWhat* pWhat, SFindHow* pHow)
	: SOperation(NULL)
	, _How(pHow)
	, _Method(pMethod)
	, AddressOfSignature(0)
{
	pWhat->SetRoot(this);

	_Method->SetOptScanning(this);
	_How->SetOptScanning(this);

	_WhatList.append(pWhat);
}

SOptScanning::SOptScanning(SFindMethod* pMethod, SWhatList whats, SFindHow* pHow)
	: SOperation(NULL)
	, _WhatList(whats)
	, _How(pHow)
	, _Method(pMethod)
	, AddressOfSignature(0)
{
	for (auto pWhat : _WhatList)
	{
		pWhat->SetRoot(this);
	}

	_Method->SetOptScanning(this);
	_How->SetOptScanning(this);
}

SOptScanning::~SOptScanning()
{
}

void SOptScanning::Start()
{
	_Time.start();
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

bool SOptScanning::WaitForDone()
{
	return _Method->wait();
}

SFindHow* SOptScanning::GetHow()
{
	return _How;
}

SWhatList& SOptScanning::GetWhatList()
{
	return _WhatList;
}


quint64 SOptScanning::GetFirstAddress()
{
	for (auto pWhat : _WhatList)
	{
		auto addrs = pWhat->GetAddresses();
		if (addrs.count() > 0) {
			return addrs.first();
		}
	}

	return 0;
}

void SOptScanning::OutputDebugElapse()
{
	qDebug("%s execute %d ms", typeid(*this).name(), _Time.elapsed());
}
