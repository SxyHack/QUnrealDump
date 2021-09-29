#pragma once

#include "SFindHow.h"
#include <QList>

#define TABLE_NEXT_SIZE 0x101
#define QUATO

class SOptScanning;

//
// �ڴ��������������
// 
class SFindHowSunday : public SFindHow
{
	Q_OBJECT

public:
	SFindHowSunday(const QVariant& vTarget, bool bIsHex = true);
	~SFindHowSunday();

	bool Judge(quint8* pBuffer, qint32 nSize, quint64& nOutAddr) override;

protected:
	void InitTableNext();

	// Hex �ַ���ת�����ֽڼ�
	bool HexStringToBytes();
	bool CharToBytes();


protected:
	QList<qint16> _TargetHexArray;
	qint16        _TableNext[TABLE_NEXT_SIZE];
};
