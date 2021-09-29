#include "SFindHowEqual.h"

SFindHowEqual::SFindHowEqual(const QVariant& vTarget)
	: SFindHow(vTarget)
{
}

SFindHowEqual::~SFindHowEqual()
{
}

bool SFindHowEqual::Judge(quint8 value)
{
	return QVariant(value) == _Target;
}

bool SFindHowEqual::Judge(quint16 value)
{
	return QVariant((quint16)value) == _Target;
}

bool SFindHowEqual::Judge(quint32 value)
{
	return QVariant((quint32)value) == _Target;
}

bool SFindHowEqual::Judge(quint64 value)
{
	return QVariant((quint64)value) == _Target;
}

bool SFindHowEqual::Judge(float value)
{
	return QVariant((float)value) == _Target;
}

bool SFindHowEqual::Judge(double value)
{
	return QVariant((double)value) == _Target;
}

bool SFindHowEqual::Judge(const QString& value)
{
	return value == _Target.toString();
}
