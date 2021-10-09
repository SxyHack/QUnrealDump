#include <QtCore/QCoreApplication>
#include "log/CustomLogMessageHandler.h"
#include "SOptScanning.h"
#include "SFindInteger.h"
#include "SFindSignature.h"

#include "SFindHowEqual.h"
#include "SFindHowSunday.h"
#include "SFindHowPattern.h"
#include "SFindMethodFast.h"
#include "SFindMethodParallel.h"
#include "SProcess.h"
#include "utility/Elapsed.h"

#include "test.h"

int main(int argc, char *argv[])
{
	auto& handler = CustomLogMessageHandler::Instance();
	qInstallMessageHandler(CustomLogMessageHandler::handle);

    QCoreApplication a(argc, argv);
    
    qDebug() << "Test Debug";
    qInfo() << "Test Info" << argc << a.arguments();
    qWarning() << "Test Warning";
    qCritical() << "Test Critical";
	//qFatal("Test Fatal");

 //   QVariant A(1.12345678911);
 //   QVariant B(1.12345678912);
 //   qDebug("Check QVariant Float: %s", (A == B) ? "true" : "false");
 //   
 //   QVariant C("\x11\x22\x33");
	//QVariant D("\x11\x22\x34");
	//qDebug("Check QVariant Bytes: %s", (C == D) ? "true" : "false");

    if (!GProcess.NtOpen(14124))
        return -1;

    GProcess.SetupAccessor(false);

    SOptScanning opt(new SFindMethodFast, 
        new SFindSignature,
        new SFindHowPattern("40 55 57 48 81 EC E8 00 00 00") // 0x7ff66e842140
        //new SFindHowPattern("48 83 EC 28 48 8B 05 F5 6D 67 05 48 85 C0")
        //new SFindHowPattern("4E 6F 6E 65 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 42 79 74 65 50 72 6F 70 65 72 74 79")
		//new SFindHowEqual("\x4E\x6F\x6E\x65????????????????????\x42\x79\x74\x65\x50\x72\x6F\x70\x65\x72\x74\x79"));
    );
    opt.Start();
    opt.WaitForDone();
    auto nAddress = opt.GetFirstAddress();
    qDebug("GNames: %p", nAddress);
    
    //typedef int (*fn)();

    //fn pFun = (fn)(nAddress);
    //auto vB = pFun();
    auto vB = CallFunc(nAddress);
	qDebug("GetA: %d", vB);

    a.exec();

	handler.Stop();
    return 0;
}
