#include "SFindWhat.h"
#include "SOptScanning.h"

SFindWhat::SFindWhat(qint32 nSize, bool bFindFirst)
	: QObject(nullptr)
	, _Operation(nullptr)
	, _Size(nSize)
	, _FindFirst(bFindFirst)
{
}

SFindWhat::~SFindWhat()
{
}

void SFindWhat::SetRoot(SOptScanning* pOperation)
{
	_Operation = pOperation;
}

qint32 SFindWhat::GetSize()
{
	return _Size;
}
