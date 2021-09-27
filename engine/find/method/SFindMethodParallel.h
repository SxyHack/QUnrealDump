#pragma once

#include "SFindMethod.h"
#include <QThreadPool>

#define PARALLEL_COUNT 128

class SFindMethodParallel : public SFindMethod
{
	Q_OBJECT

public:
	quint64 RegionBegAddrs[PARALLEL_COUNT] = {0};
	quint64 RegionEndAddrs[PARALLEL_COUNT] = {0};

public:
	SFindMethodParallel();
	~SFindMethodParallel();

protected:
	void run() override;

private:
	QThreadPool _ThreadPool;
};
