#pragma once

#include "global.h"

class SProcess
{
protected:
	SProcess();
	~SProcess();

public:
	static SProcess& Get();

public:
	//
	// �򿪽���
	//
	BOOL Open(quint64 nPID);
	BOOL NtOpen(quint64 nPID);
	BOOL IsOpen();
	void Close();

	// 
	// ��ʼ���ڴ������
	// [IN] bInternal ��True��������ע��ʽ, ��False����Ϊ���ʽ
	// 
	void SetupAccessor(bool bInternal = true);

	bool ReadInt8(quint64 nAddress, quint8& value);
	bool ReadInt16(quint64 nAddress, quint16& value);
	bool ReadInt32(quint64 nAddress, quint32& value);
	bool ReadInt64(quint64 nAddress, quint64& value);
	bool ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer);

	//
	// ���ؽ��̾��
	//
	HANDLE GetHandle();

	quint64 GetNumberOfProcessor();
	quint64 GetBegAddress();
	quint64 GetEndAddress();
	quint64 GetSize();
};


#define GProcess SProcess::Get()
