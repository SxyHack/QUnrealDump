#include "SDumpNames.h"
#include "SOptScanning.h"
#include "SFindSignature.h"
#include "SFindHowPattern.h"
#include "SFindMethodFast.h"

SDumpNames::SDumpNames(QObject *parent)
	: QThread(parent)
{
}

SDumpNames::~SDumpNames()
{
}

void SDumpNames::run()
{
	SOptScanning operation(new SFindMethodFast, new SFindSignature,
		new SFindHowPattern("4E 6F 6E 65 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 42 79 74 65 50 72 6F 70 65 72 74 79")
	);
	operation.Start();
	operation.WaitForDone();
	operation.AddressOfSignature;

}
