#include <QtCore/QCoreApplication>
#include "log\CustomLogMessageHandler.h"


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

    a.exec();

	handler.Stop();
    return 0;
}
