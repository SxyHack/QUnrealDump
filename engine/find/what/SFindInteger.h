#pragma once

#include "SFindWhat.h"

class SFindInteger : public SFindWhat
{
	Q_OBJECT

public:
	SFindInteger(quint8 nByteSize);
	~SFindInteger();

	//
	// 在传入的内存区域查找数值
	//
	bool Lookup(quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) override;
};
