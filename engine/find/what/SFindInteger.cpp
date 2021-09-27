#include "SFindInteger.h"
#include "SOptScanning.h"

SFindInteger::SFindInteger(quint8 nByteSize)
	: SFindWhat(nByteSize)
{
}

SFindInteger::~SFindInteger()
{
}

bool SFindInteger::Lookup(quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow)
{
	bool bFound = false;

	for (int i = 0; i < nBufferSize; i += _Size)
	{
		if (_Operation->IsStopped())
			break;

		switch (_Size)
		{
		case 1: bFound = pHow->Judge(*(quint8*)(pBuffer + i)); break;
		case 2: bFound = pHow->Judge(*(quint16*)(pBuffer + i)); break;
		case 4: bFound = pHow->Judge(*(quint32*)(pBuffer + i)); break;
		case 8: bFound = pHow->Judge(*(quint64*)(pBuffer + i)); break;
		}

		if (bFound)
		{
			qDebug("Found Target %d at 0x%p", pHow->GetTarget().toULongLong(), pBuffer + i);

			if (_FindFirst) {
				_Operation->Stop();
				return true;
			}
		}
	}

	return false;
}
