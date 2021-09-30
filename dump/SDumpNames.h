#pragma once

#include <QThread>

class SDumpNames : public QThread
{
	Q_OBJECT

public:
	SDumpNames(QObject *parent);
	~SDumpNames();

	void run() override;

};
