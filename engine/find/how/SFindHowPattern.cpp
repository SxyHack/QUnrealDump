#include "SFindHowPattern.h"

SFindHowPattern::SFindHowPattern(const QVariant& vTarget)
	: SFindHow(vTarget)
	, _MemoryPattern(vTarget)
{
}

SFindHowPattern::~SFindHowPattern()
{
}

bool SFindHowPattern::Judge(quint8* pBuffer, qint32 nSize, qint64& nOffset)
{
	nOffset = _MemoryPattern.FindInBuffer(pBuffer, nSize);
	return (nOffset >= 0);
}
