#include "SFindMethod.h"
#include "SOptScanning.h"
#include "SProcess.h"

// ������������,һ������δ�С���ᳬ��
#define REGION_MAX_SIZE 0x0f000000


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
		qWarning("ɨ������������.");
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
	// �Ƿ��д
	bool bWritable =
		(mbi.Protect & PAGE_READWRITE) ||
		(mbi.Protect & PAGE_WRITECOPY) ||
		(mbi.Protect & PAGE_EXECUTE_READWRITE) ||
		(mbi.Protect & PAGE_EXECUTE_WRITECOPY);

	// �Ƿ��ִ��
	bool bExecutable =
		(mbi.Protect & PAGE_EXECUTE) ||
		(mbi.Protect & PAGE_EXECUTE_READ) ||
		(mbi.Protect & PAGE_EXECUTE_READWRITE) ||
		(mbi.Protect & PAGE_EXECUTE_WRITECOPY);

	bool bCopyOnWrite =
		(mbi.Protect & PAGE_WRITECOPY) ||
		(mbi.Protect & PAGE_EXECUTE_WRITECOPY);

	//bool bValidRegion = (mbi.State == MEM_COMMIT);
	//bValidRegion = bValidRegion & ((quint64)mbi.BaseAddress < GProcess.GetEndAddress());
	//bValidRegion = bValidRegion & ((mbi.Protect & PAGE_GUARD) == 0);
	//bValidRegion = bValidRegion & ((mbi.Protect & PAGE_NOACCESS) == 0);
	//bValidRegion = bValidRegion & !(!_Operation->EnableRegionPrivate && (mbi.Type == MEM_PRIVATE));
	//bValidRegion = bValidRegion & !(!_Operation->EnableRegionImage && (mbi.Type == MEM_IMAGE));
	//bValidRegion = bValidRegion & !(!_Operation->EnableRegionMapped && (mbi.Type == MEM_MAPPED));
	//bValidRegion = bValidRegion & !((mbi.Type & PAGE_NOCACHE) > 0);
	//bValidRegion = bValidRegion & !((mbi.Type & PAGE_WRITECOMBINE) > 0);
	//return bValidRegion; // &bWritable& bExecutable& bCopyOnWrite;


	if (mbi.RegionSize <= 0 || 
		mbi.RegionSize > REGION_MAX_SIZE)
		return false;

	if (mbi.State != MEM_COMMIT)
		return false;

	bool bExcludeProtect =
		(mbi.Protect & PAGE_WRITECOPY) ||
		(mbi.Protect & PAGE_NOCACHE) ||
		(mbi.Protect & PAGE_NOACCESS) ||
		(mbi.Protect & PAGE_GUARD) ||
		(mbi.Protect & PAGE_WRITECOMBINE) ||
		(mbi.Protect & PAGE_TARGETS_INVALID) ||
		(mbi.Protect == 0);

	if (bExcludeProtect)
		return false;

	switch (mbi.Type)
	{
	case MEM_MAPPED: return _Operation->EnableRegionMapped;
	case MEM_PRIVATE: return _Operation->EnableRegionPrivate;
	case MEM_IMAGE: return _Operation->EnableRegionImage;
	}

	return true;
	//// �����дʱ����������
	//if ((mbi.Protect & PAGE_WRITECOPY) ||
	//	(mbi.Protect & PAGE_NOCACHE) ||
	//	(mbi.Protect & PAGE_NOACCESS) ||
	//	(mbi.Protect & PAGE_GUARD) ||
	//	(mbi.Protect & PAGE_WRITECOMBINE) ||
	//	(mbi.Protect & PAGE_TARGETS_INVALID) ||
	//	(mbi.Protect == 0))
	//	return false;

	//// �����MEM_MAPPED������������Ƿ�����
	//if (mbi.Type == MEM_MAPPED)
	//	return _Operation->EnableRegionMapped;

	//return true;
}

bool SFindMethod::IsCodeRegion(const MEMORY_BASIC_INFORMATION& mbi)
{
	return
		(mbi.Protect & PAGE_EXECUTE) ||
		(mbi.Protect & PAGE_EXECUTE_READ) ||
		(mbi.Protect & PAGE_EXECUTE_READWRITE) ||
		(mbi.Protect & PAGE_EXECUTE_WRITECOPY);
}
