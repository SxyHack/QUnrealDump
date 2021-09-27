#include <QtCore/QCoreApplication>
#include "log/CustomLogMessageHandler.h"
#include "SOptScanning.h"
#include "SFindInteger.h"
#include "SFindHowEqual.h"
#include "SFindMethodFast.h"
#include "SFindMethodParallel.h"
#include "SProcess.h"
#include "utility/Elapsed.h"

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

    QVariant A(1.12345678911);
    QVariant B(1.12345678912);
    qDebug("Check QVariant Float: %s", (A == B) ? "true" : "false");
    
    QVariant C("\x11\x22\x33");
	QVariant D("\x11\x22\x34");
	qDebug("Check QVariant Bytes: %s", (C == D) ? "true" : "false");

    if (!GProcess.NtOpen(21896)) 
    {
        return -1;
    }

    GProcess.SetupAccessor(false);

    SOptScanning opt(new SFindInteger(4), 
        new SFindHowEqual(0xFF), 
        new SFindMethodFast);
    opt.Start();

    a.exec();

	handler.Stop();
    return 0;
}
