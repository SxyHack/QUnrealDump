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

	InitTableNext();
}

SFindHowSunday::~SFindHowSunday()
{
}

bool SFindHowSunday::Judge(quint8* pBuffer, qint32 nSize, quint64& nOutAddr)
{
	//if (nSize % 2 > 0)
	//	return false;

	//DWORD nHalfSize = nSize / 2;
	//char* pHexBuffer = new char[nHalfSize + 1];
	//DWORD tableP[0x100];
	//qint32 i = -1;
	qint32 nTargetLength = _TargetHexArray.length();

	for (int i = 0, j, k; i < nSize;)
	{
		j = i;
		k = 0;
		for (; k < nTargetLength &&
			j < nSize &&
			_TargetHexArray[k] == pBuffer[j] ||
			_TargetHexArray[k] == CONST_QUOTE; k++, j++);

		if (k == nTargetLength)
		{
			nOutAddr = (quint64)pBuffer + i;
			return true;
		}

		if ((i + nTargetLength) >= nSize)
			return false;

		int num = _TableNext[pBuffer[i + nTargetLength]];
		if (num == -1)
			i += nTargetLength - _TableNext[CONST_QUOTE];
		else
			i += nTargetLength - num;
	}

	return false;
}

bool SFindHowSunday::HexStringToBytes()
{
	auto qTarget = _Target.toString().simplified();
	// 如果包含空格，将空格过滤掉
	if (qTarget.contains(' ')) {
		qTarget.remove(' ');
	}

	// 检查字符串长度, 必须是2的倍数
	if (qTarget.length() % 2 > 0)
		return false;

	_TargetHexArray.clear();

	for (int i = 0; i < qTarget.length(); i += 2)
	{
		auto ch = qTarget.mid(i, 2);
		if (ch == "??")
		{
			_TargetHexArray.append(CONST_QUOTE);
		}
		else
		{
			auto nValue = ch.toShort(nullptr, 16);
			_TargetHexArray.append(nValue);
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
			_TargetHexArray.append(CONST_QUOTE);
		}
		else
		{
			_TargetHexArray.append(ch);
		}
	}

	return true;
}

void SFindHowSunday::InitTableNext()
{
	for (int i = 0; i < TABLE_NEXT_SIZE; i++)
	{
		_TableNext[i] = -1;
	}

	for (int i = 0; i < TABLE_NEXT_SIZE; i++)
	{
		auto p = _TargetHexArray.at(i);
		_TableNext[p] = i;
	}
}
