#include "SParallelQueryRegion.h"
#include "SProcess.h"
#include "SOptScanning.h"
#include "microsoft/SWinFormat.h"
#include "utility/Elapsed.h"

SParallelQueryRegion::SParallelQueryRegion(SFindMethodParallel* pMethod, qint32 nIndex)
	: QRunnable()
	, _Index(nIndex)
	, _Method(pMethod)
	, _Operation(_Method->GetOptScanning())
{
}

SParallelQueryRegion::~SParallelQueryRegion()
{
	qDebug("~Query: %d", _Index);
}

void SParallelQueryRegion::run()
{
	qDebug("Query Region: %d [0x%p, 0x%p]", _Index, _Method->RegionBegAddrs[_Index], _Method->RegionEndAddrs[_Index]);

	TCHAR szModName[MAX_FILE_PATH_SIZE] = { 0 };
	HANDLE hProcess = GProcess.GetHandle();

	for (auto pWhat : _Operation->GetWhatList())
	{
		SElapsed elapse(QString("VirtualQueryEx:%1").arg(_Index));
		quint64 nQueryAddress = _Method->RegionBegAddrs[_Index];
		quint64 nReginEndAddr = _Method->RegionEndAddrs[_Index];

		MEMORY_BASIC_INFORMATION MBI;
		ZeroMemory(&MBI, sizeof(MBI));

		while (::VirtualQueryEx(hProcess, (LPVOID)nQueryAddress, &MBI, sizeof(MBI)))
		{
			//if (_Method->_Stop.tryAcquire()) {
			//	_Stop.release();
			//	return;
			//}

			QByteArray qByteArray;
			QString qModuleName;
			quint32 nRetryCount = 1;
			quint64 nRegionBegAddr = (quint64)MBI.BaseAddress;
			quint64 nRegionEndAddr = (quint64)MBI.BaseAddress + MBI.RegionSize - 1;
			quint64 nRegionNextAddress = nRegionBegAddr + MBI.RegionSize;
			quint64 nRegionWorkSize = 0x8000;

			QString qAllocProtect = WinApi::FormatMemProtect(MBI.AllocationProtect);
			QString qMemProtect   = WinApi::FormatMemProtect(MBI.Protect);
			QString qMemState     = WinApi::FormatMemState(MBI.State);
			QString qMemType      = WinApi::FormatMemType(MBI.Type);

			if (!_Method->IsValidRegion(MBI))
			{
				goto LOOP_END;
			}

			//qDebug("MemRegion:%p [%s] [%s] [%s]",
			//	MBI.BaseAddress,
			//	qMemProtect.toUtf8().data(),
			//	qMemState.toUtf8().data(),
			//	qMemType.toUtf8().data());

		LOOP_END:
			if (nRegionNextAddress <= nQueryAddress || nRegionNextAddress >= nReginEndAddr)
				break;
			nQueryAddress = nRegionNextAddress;
		}
	}
}
