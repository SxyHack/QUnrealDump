#include "SFindDouble.h"

SFindDouble::SFindDouble()
	: SFindWhat(sizeof(double))
{
}

SFindDouble::~SFindDouble()
{
}

bool SFindDouble::Lookup(quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow)
{
	return false;
}
