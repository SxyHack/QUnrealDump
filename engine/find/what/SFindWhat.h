#pragma once

#include <QObject>
#include <windows.h>
#include "SFindHow.h"

class SOptScanning;


//
// 找什么, 基类
//
class SFindWhat : public QObject
{
	Q_OBJECT

public:
	SFindWhat(qint32 nSize, bool bFindFirst = true);
	~SFindWhat();

	// 返回数据大小
	qint32 GetSize();

	void SetRoot(SOptScanning* pOperation);

	virtual bool Lookup(quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) = 0;

protected:
	SOptScanning* _Operation;
	qint32 _Size;
	bool   _FindFirst;   // true 表示只找一个, 否则找到全部匹配数值.
};

typedef QList<SFindWhat*> SWhatList;
