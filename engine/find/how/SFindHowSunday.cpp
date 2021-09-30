#include "SFindHowSunday.h"
#include <windows.h>

#define CONST_QUOTE 0x100

SFindHowSunday::SFindHowSunday(const QVariant& vTarget, bool bIsHex)
	: SFindHow(vTarget)
{
	if (bIsHex)
	{
		HexStringToBytes();
	}
	else
	{
		CharToBytes();
	}

	InitNextTable();
}

SFindHowSunday::~SFindHowSunday()
{
}

bool SFindHowSunday::Judge(quint8* pBuffer, qint32 nSize, qint64& nOffset)
{
	qint32 nDLen = nSize; // n
	qint32 nPLen = _PatternArray.length(); // m

	int i = nPLen - 1;
	while (i < nDLen) {
		int k = 0;
		while (k < nPLen && _PatternArray[nPLen - k - 1] == pBuffer[i - k]) {
			k++;
		}

		if (k == nPLen) {
			nOffset = i - nPLen + 1;
			qDebug("Sunday: 0x%p", nOffset);
			return true;
		}

		i += _Shift.contains(pBuffer[i]) ? _Shift.value(pBuffer[i]) : nPLen;
	}

	return false;
}

bool SFindHowSunday::HexStringToBytes()
{
	auto qTarget = _Target.toString().simplified();
	// ��������ո񣬽��ո���˵�
	if (qTarget.contains(' ')) {
		qTarget.remove(' ');
	}

	// ����ַ�������, ������2�ı���
	if (qTarget.length() % 2 > 0)
		return false;

	_PatternArray.clear();

	for (int i = 0; i < qTarget.length(); i += 2)
	{
		auto ch = qTarget.mid(i, 2);
		if (ch == "??")
		{
			_PatternArray.append(CONST_QUOTE);
		}
		else
		{
			auto nValue = ch.toShort(nullptr, 16);
			_PatternArray.append(nValue);
		}
	}

	return true;
}

bool SFindHowSunday::CharToBytes()
{
	auto qBytes = _Target.toByteArray();

	for (int i = 0; i < qBytes.length(); i++)
	{
		auto ch = qBytes.at(i);
		if (ch == '?')
		{
			_PatternArray.append(CONST_QUOTE);
		}
		else
		{
			_PatternArray.append(ch);
		}
	}

	return true;
}

void SFindHowSunday::InitNextTable()
{
	qint32 nPatternLength = _PatternArray.length();

	for (int i = 0; i < nPatternLength; i++)
	{
		_Shift.insert(_PatternArray[i], nPatternLength - i - 1);
	}
}


// �ο� https://blog.csdn.net/Simon798/article/details/109580472
