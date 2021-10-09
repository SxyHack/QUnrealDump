#pragma once

#include <QThread>

class SDumpNames : public QThread
{
	Q_OBJECT

public:
	SDumpNames();
	~SDumpNames();

	void run() override;

};
