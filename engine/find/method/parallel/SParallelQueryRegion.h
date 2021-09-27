#pragma once

#include <QRunnable>

#include "SFindMethodParallel.h"

class SParallelQueryRegion : public QRunnable
{
public:
	SParallelQueryRegion(SFindMethodParallel* pMethod, qint32 nIndex);
	~SParallelQueryRegion();

	void run() override;

protected:
	qint32 _Index;
	SFindMethodParallel* _Method;
	SOptScanning* _Operation;
};
