#pragma once

#include "SFindWhat.h"

class SFindDouble : public SFindWhat
{
	Q_OBJECT

public:
	SFindDouble();
	~SFindDouble();

	bool Lookup(quint64 nAddress, quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) override;

protected:
	double _Target;
};
