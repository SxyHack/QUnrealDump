#include "SProcess.h"
#include "microsoft\SLastError.h"
#include "microsoft\ntdll\ntdll.h"

static HANDLE  gProcessHandle = NULL;
static quint64 gBaseAddress = 0;
static quint64 gProcessID = 0;

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
	if (gProcessHandle)
	{
		CloseHandle(gProcessHandle);
	}

	gProcessHandle = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, nPID);
	if (gProcessHandle == NULL)
	{
		SLastError lastError;
		qCritical("OpenProcess[%d] failed, REASON:0x%x DETAIL:%s", 
			nPID,
			lastError, 
			lastError.ToString());
		return FALSE;
	}

	gProcessID = nPID;

	return TRUE;
}

BOOL SProcess::NtOpen(quint64 nPID)
{
	if (gProcessHandle)
	{
		CloseHandle(gProcessHandle);
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
	status = NtOpenProcess(&gProcessHandle,
		PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE | PROCESS_VM_READ |
		PROCESS_SUSPEND_RESUME | PROCESS_QUERY_INFORMATION,
		&objectAttributes,
		&clientId);

	if (!NT_SUCCESS(status))
	{
		/* Fail */
		SLastError lastError(status);
		//NtErrToWinError(status);
		qCritical("NtOpen(%d) Failed, REASON: %d, DETAIL:%s", nPID, lastError.ErrorCode, lastError.ToString());
		return FALSE;
	}

	gProcessID = nPID;

	/* Return the handle */
	return TRUE;
}

HANDLE SProcess::GetHandle()
{
	return gProcessHandle;
}

quint64 SProcess::GetBaseAddress()
{
	if (gBaseAddress > 0)
	{
		return gBaseAddress;
	}

	MODULEENTRY32 moduleEntry;

	// 获取进程快照中包含在th32ProcessID中指定的进程的所有的模块。
	HANDLE hSnapshot = ::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, gProcessID); 
	if (hSnapshot == NULL) 
	{
		SLastError lastError;
		qCritical("Call CreateToolhelp32Snapshot() Failed, REASON:%x, DETAIL:%s", lastError, lastError.ToString());
		return NULL;
	}

	ZeroMemory(&moduleEntry, sizeof(MODULEENTRY32));
	moduleEntry.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(hSnapshot, &moduleEntry)) 
	{
		CloseHandle(hSnapshot);
		return NULL;
	}

	CloseHandle(hSnapshot);
	gBaseAddress = (quint64)moduleEntry.hModule;

	return gBaseAddress;
}
