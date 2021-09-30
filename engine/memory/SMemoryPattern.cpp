#include "SMemoryPattern.h"

static inline bool IsHex(QChar ch)
{
	return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f');
}

SMemoryPattern::SMemoryPattern(const QVariant& vPattern, bool bIsHex)
{
	HexStringToBytes(vPattern.toString());
}

SMemoryPattern::~SMemoryPattern()
{
}

qint64 SMemoryPattern::FindInBuffer(quint8* pBuffer, qint32 nBufferSize)
{
	qint32 nPatternSize = _Pattern.length();
	for (int i = 0, pos = 0; i < nBufferSize; i++)
	{
		if (PatternMatchByte(pBuffer[i], _Pattern.at(pos)))
		{
			pos++;
			if (pos == nPatternSize)
			{
				return i - nPatternSize + 1;
			}
		}
		else if (pos > 0)
		{
			i -= pos;
			pos = 0;
		}
	}

	return -1;
}

bool SMemoryPattern::HexStringToBytes(const QString& pattern)
{
	auto qPattern = pattern.simplified();
	// 如果包含空格，将空格过滤掉
	if (qPattern.contains(' ')) {
		qPattern.remove(' ');
	}

	// 检查字符串长度, 必须是2的倍数
	if (qPattern.length() % 2)
		return false;

	_Pattern.clear();
	bool bAllWildcard = true;
	Byte newByte;

	for (int i = 0, j = 0; i < qPattern.length(); i++)
	{
		auto ch = qPattern.at(i);
		if (ch == '?')
		{
			newByte.nibble[j].bWildcard = true;
		}
		else if (!IsHex(ch))
		{
			return false;
		}
		else
		{
			auto nInt = QString(ch).toUInt(nullptr, 16);
			bAllWildcard = false;
			newByte.nibble[j].bWildcard = false;
			newByte.nibble[j].data = nInt & 0xF;
		}

		j++;
		if (j == 2) {
			j = 0;
			_Pattern.append(newByte);
		}
	}

	if (bAllWildcard)
		return false;

	return true;
}

bool SMemoryPattern::CharToBytes(const QString& pattern)
{
	return false;
}

bool SMemoryPattern::PatternMatchByte(quint8 nByte, const Byte& pByte)
{
	int matched = 0;

	unsigned char n1 = (nByte >> 4) & 0xF;
	if (pByte.nibble[0].bWildcard)
		matched++;
	else if (pByte.nibble[0].data == n1)
		matched++;

	unsigned char n2 = nByte & 0xF;
	if (pByte.nibble[1].bWildcard)
		matched++;
	else if (pByte.nibble[1].data == n2)
		matched++;

	return (matched == 2);
}
