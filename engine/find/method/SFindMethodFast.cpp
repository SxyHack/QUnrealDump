#include "SFindMethodFast.h"
#include "SProcess.h"
#include "SOptScanning.h"
#include "SFastWorker.h"
#include "SFindWhat.h"

#include "microsoft/SWinFormat.h"
#include "utility/Elapsed.h"



SFindMethodFast::SFindMethodFast()
	: SFindMethod()
	, _Dispatcher(this)
{
	_ThreadPool.setMaxThreadCount(GProcess.GetNumberOfProcessor());
}

SFindMethodFast::~SFindMethodFast()
{
}

void SFindMethodFast::StartWorker(SFastWorker* pWorker)
{
	_ThreadPool.start(pWorker);
}

void SFindMethodFast::Stop()
{
	SFindMethod::Stop();

	_Dispatcher.Stop(); 
}

void SFindMethodFast::run()
{
	SElapsed elapse("VirtualQueryEx");

	HANDLE hProcess = GProcess.GetHandle();
	quint64 nProcessBegAddr = GProcess.GetBegAddress();
	quint64 nProcessEndAddr = GProcess.GetEndAddress();

	auto& whats = _Operation->GetWhatList();

	if (nProcessBegAddr % 8 > 0) {
		nProcessBegAddr = nProcessBegAddr - nProcessBegAddr % 8;
	}

	MEMORY_BASIC_INFORMATION MBI;
	ZeroMemory(&MBI, sizeof(MBI));

	while (::VirtualQueryEx(hProcess, (LPVOID)nProcessBegAddr, &MBI, sizeof(MBI)))
	{
		quint64 nRegionBegAddr = (quint64)MBI.BaseAddress;
		quint64 nRegionNextAddress = nRegionBegAddr + MBI.RegionSize;

		if (nRegionBegAddr < nProcessBegAddr) {
			nRegionBegAddr = nProcessBegAddr;
			MBI.RegionSize -= nProcessBegAddr - nRegionBegAddr;
		}

		if (nRegionBegAddr + MBI.RegionSize >= nProcessEndAddr)	{
			MBI.RegionSize = nProcessEndAddr - nRegionBegAddr;
		}

		quint64 nRegionEndAddr = nRegionBegAddr + MBI.RegionSize;


		//QString qMemProtect = WinApi::FormatMemProtect(MBI.Protect);
		//QString qMemState = WinApi::FormatMemState(MBI.State);
		//QString qMemType = WinApi::FormatMemType(MBI.Type);
		//qDebug("Region:[%p - %p] Size:%d [%s] <%s> {%s}",
		//	nRegionBegAddr,
		//	nRegionEndAddr,
		//	MBI.RegionSize,
		//	qMemProtect.toUtf8().data(),
		//	qMemState.toUtf8().data(),
		//	qMemType.toUtf8().data()
		//);

		if (IsValidRegion(MBI))
		{
			_Workers.append(new SFastWorker(nRegionBegAddr, nRegionEndAddr, this, whats));
		}

	LOOP_NEXT:
		if (nRegionNextAddress <= nProcessBegAddr || 
			nRegionNextAddress >= GProcess.GetEndAddress()) 
			break;
		nProcessBegAddr = nRegionNextAddress;
	}

	qDebug("有效内存页数量：%d", _Workers.count());
	//_Dispatcher.start(QThread::HighestPriority);

	for (auto pWorker : _Workers)
	{
		_ThreadPool.start(pWorker);
	}

	_ThreadPool.waitForDone();
	qInfo("扫描完成");
}