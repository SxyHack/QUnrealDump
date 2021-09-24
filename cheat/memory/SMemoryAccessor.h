#pragma once

#include <QObject>

//
// 内存访问接口
//
class SMemoryAccessor
{
public:
	SMemoryAccessor();
	~SMemoryAccessor();

	//
	// 读取内存
	// [IN] nAddress 传入地址
	// [RETURN] quint8 返回地址的内存
	//
	virtual quint8  ReadInt8(quint64 nAddress) = 0;
	virtual quint16 ReadInt16(quint64 nAddress) = 0;
	virtual quint32 ReadInt32(quint64 nAddress) = 0;
	virtual quint64 ReadInt64(quint64 nAddress) = 0;

};
