#pragma once

#include "SFindWhat.h"

class SFindInteger : public SFindWhat
{
	Q_OBJECT

public:
	SFindInteger(quint8 nByteSize);
	~SFindInteger();

	//
	// �ڴ�����ڴ����������ֵ
	//
	bool Lookup(quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) override;
};
