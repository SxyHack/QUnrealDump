#pragma once

#include "SFindHow.h"

class SOptScanning;

//
// ��ȷ���ң����ǵ���
//
class SFindHowEqual : public SFindHow
{
	Q_OBJECT

public:
	SFindHowEqual(const QVariant& vTarget);
	~SFindHowEqual();

	bool Judge(quint8 value) override;
	bool Judge(quint16 value) override;
	bool Judge(quint32 value) override;
	bool Judge(quint64 value) override;
	
	bool Judge(float value) override;
	bool Judge(double value) override;

	bool Judge(const QString& value) override;
};
