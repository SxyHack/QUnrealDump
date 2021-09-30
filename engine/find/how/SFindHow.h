#pragma once

#include <QObject>
#include <QVariant>

class SOptScanning;

//
// ‘ı√¥≈–∂œ
//
class SFindHow : public QObject
{
	Q_OBJECT

public:
	SFindHow(const QVariant& vTarget);
	~SFindHow();

	void SetOptScanning(SOptScanning* pOperation);
	QVariant& GetTarget();

	virtual bool Judge(quint8 value);
	virtual bool Judge(quint16 value);
	virtual bool Judge(quint32 value);
	virtual bool Judge(quint64 value);

	virtual bool Judge(float value);
	virtual bool Judge(double value);

	virtual bool Judge(const QString& value);

	virtual bool Judge(quint8* pBuffer, qint32 nSize, qint64& nOffset);

protected:
	SOptScanning* _Operation;
	QVariant      _Target;
};
