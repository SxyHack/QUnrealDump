#pragma once

#include "SFindWhat.h"

class SFindString : public SFindWhat
{
	Q_OBJECT

public:
	SFindString();
	~SFindString();

	bool Lookup(quint64 nAddress, quint8* pBuffer, quint64 nBufferSize, SFindHow* pHow) override;
};
