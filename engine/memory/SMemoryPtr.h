#pragma once

#include <QObject>

class SMemoryPtr : public QObject
{
	Q_OBJECT

public:
	SMemoryPtr(QObject *parent);
	~SMemoryPtr();
};
