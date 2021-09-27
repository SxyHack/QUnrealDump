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
	_ThreadPool.setMaxThreadCount(6);
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
	SElapsed e1("FastMethodThread");
	_Dispatcher.start(QThread::HighestPriority);

	HANDLE hProcess = GProcess.GetHandle();

	for (auto pWhat : _Operation->GetWhatList())
	{
		SElapsed elapse("VirtualQueryEx");
		quint64 nQueryAddress = GProcess.GetBegAddress();
		MEMORY_BASIC_INFORMATION MBI;
		ZeroMemory(&MBI, sizeof(MBI));

		while (::VirtualQueryEx(hProcess, (LPVOID)nQueryAddress, &MBI, sizeof(MBI)))
		{
			if (isInterruptionRequested()) 
			{
				break;
			}

			QString qModuleName;
			quint64 nRegionBegAddr = (quint64)MBI.BaseAddress;
			quint64 nRegionEndAddr = (quint64)MBI.BaseAddress + MBI.RegionSize - 1;
			quint64 nRegionNextAddress = nRegionBegAddr + MBI.RegionSize;
			quint64 nRegionWorkSize = 0x10000;

			QString qMemProtect = WinApi::FormatMemProtect(MBI.Protect);
			QString qMemState = WinApi::FormatMemState(MBI.State);
			QString qMemType = WinApi::FormatMemType(MBI.Type);

			if (IsValidRegion(MBI))
			{
				_Dispatcher.PushQueue(new SFastWorker(nRegionBegAddr, nRegionEndAddr, this, pWhat));
			}
		
		LOOP_NEXT:
			if (nRegionNextAddress <= nQueryAddress || 
				nRegionNextAddress >= GProcess.GetEndAddress()) 
				break;
			nQueryAddress = nRegionNextAddress;
		}
	}

	_ThreadPool.waitForDone();
}