#pragma once

#include <QObject>

class SOperation : public QObject
{
	Q_OBJECT

public:
	SOperation(QObject* parent = nullptr);
	~SOperation();

	virtual void Start() = 0;
	virtual void Stop() = 0;
	virtual bool IsStopped() = 0;

};
