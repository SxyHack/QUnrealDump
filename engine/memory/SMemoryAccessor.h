#pragma once

#include <QObject>

//
// �ڴ���ʽӿ�
//
class SMemoryAccessor
{
public:
	SMemoryAccessor();
	~SMemoryAccessor();

	//
	// ��ȡ�ڴ�
	// [IN] nAddress �����ַ
	// [OUT] value ���ص�ַ����ֵ
	// [RETURN] bool �Ƿ��ȡ�ɹ�
	//
	virtual bool ReadInt8(quint64 nAddress, quint8& value) = 0;
	virtual bool ReadInt16(quint64 nAddress, quint16& value) = 0;
	virtual bool ReadInt32(quint64 nAddress, quint32& value) = 0;
	virtual bool ReadInt64(quint64 nAddress, quint64& value) = 0;
	virtual bool ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer) = 0;
};
