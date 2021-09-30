#pragma once

class SOptScanning;

#include "SFindHow.h"
#include "SMemoryPattern.h"

class SFindHowPattern : public SFindHow
{
	Q_OBJECT

public:
	SFindHowPattern(const QVariant& vTarget);
	~SFindHowPattern();

	bool Judge(quint8* pBuffer, qint32 nSize, qint64& nOffset) override;

protected:
	SMemoryPattern _MemoryPattern;
};
