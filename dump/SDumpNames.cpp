#include "SDumpNames.h"
#include "SProcess.h"

SDumpNames::SDumpNames(QObject *parent)
	: QThread(parent)
{
}

SDumpNames::~SDumpNames()
{
}

void SDumpNames::run()
{
	auto nAddrOfGNames = GProcess.FindPattern("4E 6F 6E 65 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 42 79 74 65 50 72 6F 70 65 72 74 79");
}
