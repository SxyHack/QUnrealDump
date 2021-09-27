#include "SFindMethod.h"
#include "SOptScanning.h"

SFindMethod::SFindMethod() 
	: QThread()
	, _Operation(nullptr)
{
	setTerminationEnabled();
}

SFindMethod::~SFindMethod()
{
}

void SFindMethod::SetOptScanning(SOptScanning* pOperation)
{
	_Operation = pOperation;
}

SOptScanning* SFindMethod::GetOptScanning()
{
	return _Operation;
}

void SFindMethod::Start()
{
	if (isRunning()) 
	{
		qWarning("扫描正在运行中.");
		return;
	}

	start(QThread::HighestPriority);
}

void SFindMethod::Stop()
{
	requestInterruption();
}

bool SFindMethod::IsValidRegion(const MEMORY_BASIC_INFORMATION& mbi)
{
	if (mbi.RegionSize == 1)
		return false;

	if (mbi.State == MEM_FREE)
		return false;

	// 如果是写时拷贝，跳过
	if ((mbi.Protect & PAGE_WRITECOPY) ||
		(mbi.Protect & PAGE_NOCACHE) ||
		(mbi.Protect & PAGE_NOACCESS) ||
		(mbi.Protect & PAGE_GUARD) ||
		(mbi.Protect == 0))
		return false;

	// 如果是MEM_MAPPED，则根据配置是否跳过
	if ((mbi.Type & MEM_MAPPED) || (mbi.Type == MEM_MAPPED))
		return _Operation->EnableRegionMapped;

	return true;
}

bool SFindMethod::IsCodeRegion(const MEMORY_BASIC_INFORMATION& mbi)
{
	return
		(mbi.Protect & PAGE_EXECUTE) ||
		(mbi.Protect & PAGE_EXECUTE_READ) ||
		(mbi.Protect & PAGE_EXECUTE_READWRITE) ||
		(mbi.Protect & PAGE_EXECUTE_WRITECOPY);
}
