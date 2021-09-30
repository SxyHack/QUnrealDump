#include "SProcess.h"
#include "SMemoryInternalAccessor.h"
#include "SMemoryExternalAccessor.h"

#include "microsoft\SLastError.h"

#define LOG_STR_MUST_INIT_ACCESSOR "必须先调用 SetupAccessor()"


static HANDLE  _ProcessHandle = NULL;
static quint64 _BaseAddress = 0;
static quint64 _BaseModuleSize = 0;
static quint64 _ProcessID = 0;
static quint32 _NumberOfProcessors = 0;
static quint64 _ProcessBegAddress = 0;
static quint64 _ProcessEndAddress = 0;
static quint64 _ProcessSize = 0;

static SMemoryAccessor* _Accessor = nullptr;

SProcess::SProcess()
{
	SYSTEM_INFO si;
	ZeroMemory(&si, sizeof(si));
	GetSystemInfo(&si);
	_NumberOfProcessors = si.dwNumberOfProcessors;

	_ProcessBegAddress = (quint64)si.lpMinimumApplicationAddress;
	_ProcessEndAddress = (quint64)si.lpMaximumApplicationAddress;

	_ProcessSize = _ProcessEndAddress - _ProcessBegAddress;
}

SProcess::~SProcess()
{
}

SProcess& SProcess::Get()
{
	static SProcess instance;
	return instance;
}

BOOL SProcess::Open(quint64 nPID)
{
	if (_ProcessHandle)
	{
		CloseHandle(_ProcessHandle);
		Close();
	}

	_ProcessHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, nPID);
	if (_ProcessHandle == NULL)
	{
		SLastError lastError;
		qCritical("OpenProcess[%d] failed, REASON:0x%x DETAIL:%s", 
			nPID,
			lastError, 
			lastError.ToString());

		return FALSE;
	}

	_ProcessID = nPID;

	return TRUE;
}

BOOL SProcess::NtOpen(quint64 nPID)
{
	if (_ProcessHandle)
	{
		CloseHandle(_ProcessHandle);
		Close();
	}

	NTSTATUS status;
	OBJECT_ATTRIBUTES objectAttributes;
	CLIENT_ID clientId;

	/* If we don't have a PID, look it up */
	//if (dwProcessId == MAXDWORD) dwProcessId = (DWORD_PTR)CsrGetProcessId();

	/* Open a handle to the process */
	clientId.UniqueThread = NULL;
	clientId.UniqueProcess = UlongToHandle(nPID);
	InitializeObjectAttributes(&objectAttributes, NULL, 0, NULL, NULL);
	status = NtOpenProcess(&_ProcessHandle,
		PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE | PROCESS_VM_READ |
		PROCESS_SUSPEND_RESUME | PROCESS_QUERY_INFORMATION,
		&objectAttributes,
		&clientId);

	if (!NT_SUCCESS(status))
	{
		/* Fail */
		SLastError lastError(status);
		qCritical("NtOpenProcess(%d) Failed, REASON: %d, DETAIL:%s", 
			nPID, 
			lastError, 
			lastError.ToString());
		return FALSE;
	}

	_ProcessID = nPID;

	/* Return the handle */
	return TRUE;
}

BOOL SProcess::IsOpen()
{
	return _ProcessHandle != NULL;
}

void SProcess::Close()
{
	CloseHandle(_ProcessHandle);
	_ProcessHandle = NULL;
}

void SProcess::SetupAccessor(bool bInternal /*= true*/)
{
	if (_Accessor) {
		qWarning("内存访问器已经创建");
		return;
	}

	if (bInternal)
		_Accessor = new SMemoryInternalAccessor;
	else
		_Accessor = new SMemoryExternalAccessor;
}

bool SProcess::ReadInt8(quint64 nAddress, quint8& value)
{
	if (_Accessor == nullptr)
	{
		qCritical(LOG_STR_MUST_INIT_ACCESSOR);
		return false;
	}
	return _Accessor->ReadInt8(nAddress, value);
}

bool SProcess::ReadInt16(quint64 nAddress, quint16& value)
{
	if (_Accessor == nullptr)
	{
		qCritical(LOG_STR_MUST_INIT_ACCESSOR);
		return false;
	}
	return _Accessor->ReadInt16(nAddress, value);
}

bool SProcess::ReadInt32(quint64 nAddress, quint32& value)
{
	if (_Accessor == nullptr)
	{
		qCritical(LOG_STR_MUST_INIT_ACCESSOR);
		return false;
	}
	return _Accessor->ReadInt32(nAddress, value);
}

bool SProcess::ReadInt64(quint64 nAddress, quint64& value)
{
	if (_Accessor == nullptr)
	{
		qCritical(LOG_STR_MUST_INIT_ACCESSOR);
		return false;
	}
	return _Accessor->ReadInt64(nAddress, value);
}

bool SProcess::ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer)
{
	if (_Accessor == nullptr)
	{
		qCritical(LOG_STR_MUST_INIT_ACCESSOR);
		return false;
	}

	return _Accessor->ReadBytes(nAddress, nSize, pBuffer);
}

HANDLE SProcess::GetHandle()
{
	return _ProcessHandle;
}

quint64 SProcess::GetNumberOfProcessor()
{
	return _NumberOfProcessors;
}

quint64 SProcess::GetBegAddress()
{
	return _ProcessBegAddress;
}

quint64 SProcess::GetEndAddress()
{
	return _ProcessEndAddress;
}

quint64 SProcess::GetSize()
{
	return _ProcessSize;
}

//BOOL SProcess::GetBaseAddress(quint64& nAddress, DWORD& dwSize)
//{
//	MODULEENTRY32 moduleEntry;
//	ZeroMemory(&moduleEntry, sizeof(MODULEENTRY32));
//	moduleEntry.dwSize = sizeof(MODULEENTRY32);
//
//	// 获取进程快照中包含在th32ProcessID中指定的进程的所有的模块。
//	HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, _ProcessID); 
//	if (hSnapshot == NULL) 
//	{
//		SLastError lastError;
//		qCritical("Call CreateToolhelp32Snapshot(%d) Failed, REASON:%x, DETAIL:%s", 
//			_ProcessID, 
//			lastError, 
//			lastError.ToString());
//		return FALSE;
//	}
//
//	if (!Module32First(hSnapshot, &moduleEntry)) 
//	{
//		CloseHandle(hSnapshot);
//		return FALSE;
//	}
//
//	CloseHandle(hSnapshot);
//
//	nAddress = (quint64)moduleEntry.modBaseAddr;
//	dwSize = moduleEntry.modBaseSize;
//
//	return TRUE;
//}
