#include "SFindSignature.h"
#include "SFindHowSunday.h"
#include "SOptScanning.h"

SFindSignature::SFindSignature()
	: SFindWhat(0)
{
}

SFindSignature::~SFindSignature()
{
}

bool SFindSignature::Lookup(quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow)
{
	//SFindHowSunday* pEqual = dynamic_cast<SFindHowSunday*>(pHow);
	////if (typeid(pHow) != typeid(SFindHowEqual)) {
	//if (pEqual == nullptr) {
	//	qWarning("特征码扫描只支持'精确查找(SFindHowEqual)', Type:%s", typeid(*pHow).name());
	//	return false;
	//}
	qint64 nOffset = 0;
	if (pHow->Judge(pBuffer, nBufferSize, nOffset))
	{
		_Offsets.append(nOffset);
		return true;
	}

	return false;
}
