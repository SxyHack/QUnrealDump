#include "SFindMethodParallel.h"
#include "SProcess.h"
#include "SParallelQueryRegion.h"
#include "utility/Elapsed.h"

SFindMethodParallel::SFindMethodParallel()
	: SFindMethod()
	, RegionBegAddrs()
	, RegionEndAddrs()
{
}

SFindMethodParallel::~SFindMethodParallel()
{
}

void SFindMethodParallel::run()
{
	SElapsed elapse("SFindMethodParallel");

	quint64 nSize = GProcess.GetSize();
	quint64 nRegionSize = nSize / PARALLEL_COUNT;
	quint64 nRegionAlign = nRegionSize % 4;
	if (nRegionAlign != 0)
		nRegionSize += 4 - nRegionAlign;

	RegionBegAddrs[0] = GProcess.GetBegAddress();
	RegionEndAddrs[0] = GProcess.GetBegAddress() + nRegionSize;

	for (int i = 1; i < PARALLEL_COUNT; i++)
	{
		RegionBegAddrs[i] = RegionBegAddrs[i - 1] + nRegionSize;
		RegionEndAddrs[i] = qMin(RegionBegAddrs[i] + nRegionSize, GProcess.GetEndAddress());
	}

	for (int i = 0; i < PARALLEL_COUNT; i++)
	{
		_ThreadPool.start(new SParallelQueryRegion(this, i));
	}

	_ThreadPool.waitForDone();
}
