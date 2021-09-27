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

	virtual bool Judge(quint8 value) = 0;
	virtual bool Judge(quint16 value) = 0;
	virtual bool Judge(quint32 value) = 0;
	virtual bool Judge(quint64 value) = 0;

	virtual bool Judge(float value) = 0;
	virtual bool Judge(double value) = 0;

	virtual bool Judge(const QString& value) = 0;
	virtual bool Judge(quint8* pBuffer, quint8* pBufferEnd) = 0;
	//virtual bool Judge(const QByteArray& value) = 0;

protected:
	SOptScanning* _Operation;
	QVariant _Target;
};
