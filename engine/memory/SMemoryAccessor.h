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
	// [OUT] value 返回地址的数值
	// [RETURN] bool 是否读取成功
	//
	virtual bool ReadInt8(quint64 nAddress, quint8& value) = 0;
	virtual bool ReadInt16(quint64 nAddress, quint16& value) = 0;
	virtual bool ReadInt32(quint64 nAddress, quint32& value) = 0;
	virtual bool ReadInt64(quint64 nAddress, quint64& value) = 0;
	virtual bool ReadBytes(quint64 nAddress, quint64 nSize, quint8** pBuffer) = 0;
};
