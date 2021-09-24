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
	// [RETURN] quint8 ���ص�ַ���ڴ�
	//
	virtual quint8  ReadInt8(quint64 nAddress) = 0;
	virtual quint16 ReadInt16(quint64 nAddress) = 0;
	virtual quint32 ReadInt32(quint64 nAddress) = 0;
	virtual quint64 ReadInt64(quint64 nAddress) = 0;

};
