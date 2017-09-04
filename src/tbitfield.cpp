// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tbitfield.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ������� ����

#include "tbitfield.h"
#include <iostream>  
using namespace std;

TBitField::TBitField(int len)
{
	if (len < 1) throw 1;
	BitLen = len;
	MemLen = BitLen / sizeof(TELEM) * 8 + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // ����������� �����������
{
	if (bf.BitLen < 1) throw 1;
	BitLen = bf.BitLen;
	MemLen = BitLen / sizeof(TELEM) * 8 + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	if (pMem != 0) delete[] pMem;
	pMem = 0;
	BitLen = 0;
}

int TBitField::GetMemIndex(const int n) const // ����� ����� ��� n ����
{
	if (n<0) throw 2;
	if (n > BitLen) throw 2;
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // ������� ����� ��� ���� n
{
	int pos = n % (sizeof(TELEM) * 8);
	TELEM tmp = 1;
	tmp <<= pos - 1;
	return tmp;
}

// ������ � ����� �������� ����

int TBitField::GetLength(void) const // �������� ����� (�-�� �����)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // ���������� ���
{
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] |= mask;
}

void TBitField::ClrBit(const int n) // �������� ���
{
	if (n <= 0 || n > BitLen) throw 2;
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] &= ~mask;
}

int TBitField::GetBit(const int n) const // �������� �������� ����
{
	int index = GetMemIndex(n);
	TELEM tmp = (pMem[index] >> (n - 1));
	return tmp & 1;
}

// ������� ��������

TBitField& TBitField::operator=(const TBitField &bf) // ������������
{
	//delete[] this->pMem;
	BitLen = bf.BitLen;
	pMem = new TELEM[BitLen];
	//MemLen = bf.MemLen;
	for (int i = 0; i < BitLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // ���������
{
	bool check = true;
	for (int i = 0; i < this->BitLen; i++)
		if (this->pMem[i] != bf.pMem[i])
			check = false;
	return check;
}

bool TBitField::operator!=(const TBitField &bf) const // ���������
{
	return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) // �������� "���"
{
	int MinIndex = (BitLen < bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MinIndex; i++)
		pMem[i] |= bf.pMem[i];
	return *this;
}

TBitField TBitField::operator&(const TBitField &bf) // �������� "�"
{
	int MinIndex = (BitLen < bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MinIndex; i++)
		pMem[i] &= bf.pMem[i];
	return *this;
}

TBitField TBitField::operator~(void) // ���������
{
	for (int i = 0; i < BitLen; i++)
		if (this->GetBit(i))
		{
			this->ClrBit(i);
		}
		else
		{
			this->SetBit(i);
		}
	return *this;
}

// ����/�����

istream &operator>>(istream &istr, TBitField &bf) // ����
{
	for (int i = 0; i < bf.MemLen; i++)
		istr >> bf.pMem[i];
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // �����
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
