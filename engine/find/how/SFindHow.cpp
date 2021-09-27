#include "SFindHow.h"

SFindHow::SFindHow(const QVariant& vTarget)
	: QObject()
	, _Operation(nullptr)
	, _Target(vTarget)
{
}

SFindHow::~SFindHow()
{
}

void SFindHow::SetOptScanning(SOptScanning* pOperation)
{
	_Operation = pOperation;
}

QVariant& SFindHow::GetTarget()
{
	return _Target;
}

bool SFindHow::Judge(quint8* pBuffer, quint8* pBufferEnd)
{
	return false;
}
