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

bool SFindHow::Judge(quint8* pBuffer, qint32 nSize, qint64& nOffset)
{
	return false;
}

bool SFindHow::Judge(quint8 value)
{
	return false;
}

bool SFindHow::Judge(quint16 value)
{
	return false;
}

bool SFindHow::Judge(quint32 value)
{
	return false;
}

bool SFindHow::Judge(quint64 value)
{
	return false;
}

bool SFindHow::Judge(float value)
{
	return false;
}

bool SFindHow::Judge(double value)
{
	return false;
}

bool SFindHow::Judge(const QString& value)
{
	return false;
}
