#pragma once

#include <QObject>
#include <windows.h>
#include "SFindHow.h"

class SOptScanning;

typedef QList<quint64> Offsets;

//
// 找什么类型的数据, 基类
// 负责搜索逻辑。
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

	virtual bool Lookup(quint64 nAddress, quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) = 0;

	Offsets& GetOffsets();

protected:
	SOptScanning* _Operation;
	qint32        _Size;
	bool          _FindFirst;   // true 表示只找一个, 否则找到全部匹配数值.
	Offsets       _Offsets;
};


typedef QList<SFindWhat*> SWhatList;
