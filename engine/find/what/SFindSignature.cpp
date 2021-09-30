#include "SFindSignature.h"
#include "SFindHowPattern.h"
#include "SFindHowSunday.h"
#include "SOptScanning.h"

SFindSignature::SFindSignature()
	: SFindWhat(0)
{
}

SFindSignature::~SFindSignature()
{
}

bool SFindSignature::Lookup(quint64 nAddress, quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow)
{
	if (!(typeid(*pHow) == typeid(SFindHowPattern) || typeid(*pHow) == typeid(SFindHowSunday))) {
		qWarning("������ɨ��ֻ֧��'��ȷ����(SFindHowEqual)', Type:%s", typeid(*pHow).name());
		return false;
	}

	qint64 nOffset = 0;
	if (pHow->Judge(pBuffer, nBufferSize, nOffset))
	{
		qDebug("Found Signature At: [%p]", nAddress + nOffset);
		_Offsets.append(nOffset);

		_Operation->OutputDebugElapse();
		_Operation->Stop();
		return true;
	}

	return false;
}
