#include "SFindSignature.h"
#include "SFindHowEqual.h"
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
	SFindHowEqual* pEqual = dynamic_cast<SFindHowEqual*>(pHow);
	//if (typeid(pHow) != typeid(SFindHowEqual)) {
	if (pEqual == nullptr) {
		qWarning("������ɨ��ֻ֧��'��ȷ����(SFindHowEqual)', Type:%s", typeid(*pHow).name());
		return false;
	}

	quint8* pBufferEnd = pBuffer + nBufferSize - 1;

	for (int i = 0; i < nBufferSize; i++)
	{
		if (pHow->Judge(pBuffer + i, pBufferEnd))
		{
			_Operation->Stop();
			return true;
		}
	}
}
