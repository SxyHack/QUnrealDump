#pragma once

#include <QVariant>

class SMemoryPattern
{
public:
	struct Byte
	{
		struct Nibble
		{
			quint8 data;
			bool bWildcard;
		} nibble[2];
	};

	typedef QList<Byte> SPatternByteArray;

public:
	SMemoryPattern(const QVariant& vPattern, bool bIsHex = true);
	~SMemoryPattern();

	qint64 FindInBuffer(quint8* pBuffer, qint32 nBufferSize);

protected:
	// Hex 字符串转换成字节集
	bool HexStringToBytes(const QString& pattern);
	bool CharToBytes(const QString& pattern);

	bool PatternMatchByte(quint8 nByte, const Byte& pByte);

private:
	SPatternByteArray _Pattern;
};
