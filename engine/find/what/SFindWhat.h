#pragma once

#include <QObject>
#include <windows.h>
#include "SFindHow.h"

class SOptScanning;

typedef QList<quint64> Offsets;

//
// ��ʲô���͵�����, ����
// ���������߼���
//
class SFindWhat : public QObject
{
	Q_OBJECT

public:
	SFindWhat(qint32 nSize, bool bFindFirst = true);
	~SFindWhat();

	// �������ݴ�С
	qint32 GetSize();

	void SetRoot(SOptScanning* pOperation);

	virtual bool Lookup(quint64 nAddress, quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) = 0;

	Offsets& GetOffsets();

protected:
	SOptScanning* _Operation;
	qint32        _Size;
	bool          _FindFirst;   // true ��ʾֻ��һ��, �����ҵ�ȫ��ƥ����ֵ.
	Offsets       _Offsets;
};


typedef QList<SFindWhat*> SWhatList;
