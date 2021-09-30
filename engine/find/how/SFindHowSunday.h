#pragma once
class SOptScanning;

#include "SFindHow.h"
#include <QList>
#include <QMap>

#define TABLE_NEXT_SIZE 0x100 


//
// �ڴ��������������
// 
class SFindHowSunday : public SFindHow
{
	Q_OBJECT

public:
	SFindHowSunday(const QVariant& vTarget, bool bIsHex = true);
	~SFindHowSunday();

	bool Judge(quint8* pBuffer, qint32 nSize, qint64& nOffset) override;

protected:
	void InitNextTable();

	// Hex �ַ���ת�����ֽڼ�
	bool HexStringToBytes();
	bool CharToBytes();


protected:
	QList<qint16> _PatternArray;
	qint16        _TableNext[TABLE_NEXT_SIZE];

	QMap<qint16, qint16> _Shift;
};
