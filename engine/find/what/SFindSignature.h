#pragma once

#include "SFindWhat.h"

class SFindSignature : public SFindWhat
{
	Q_OBJECT

public:
	SFindSignature();
	~SFindSignature();

	bool Lookup(quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) override;
};
