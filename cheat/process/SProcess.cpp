#include "SProcess.h"
#include "microsoft\SLastError.h"

static HANDLE  _ProcessHandle = NULL;
static quint64 _BaseAddress = 0;
static quint64 _BaseModuleSize = 0;
static quint64 _ProcessID = 0;

SProcess::SProcess()
{
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

HANDLE SProcess::GetHandle()
{
	return _ProcessHandle;
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
