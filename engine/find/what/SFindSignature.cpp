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
	SFindHowSunday* pEqual = dynamic_cast<SFindHowSunday*>(pHow);
	//if (typeid(pHow) != typeid(SFindHowEqual)) {
	if (pEqual == nullptr) {
		qWarning("特征码扫描只支持'精确查找(SFindHowEqual)', Type:%s", typeid(*pHow).name());
		return false;
	}

	quint64 nAddress;
	pEqual->Judge(pBuffer, nBufferSize, nAddress);

	//quint8* pBufferEnd = pBuffer + nBufferSize - 1;

	//for (int i = 0; i < nBufferSize; i++)
	//{
	//	quint8* pCursor = pBuffer + i;
	//	if (pHow->Judge(pCursor, pBufferEnd))
	//	{
	//		qInfo("Find Signature at: 0x%p", pCursor);
	//		_Operation->Stop();
	//		return true;
	//	}
	//}

	return false;
}
