// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

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

TBitField::TBitField(const TBitField &bf) // конструктор копирования
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

int TBitField::GetMemIndex(const int n) const // номер байта для n бита
{
	if (n<0) throw 2;
	if (n > BitLen) throw 2;
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int pos = n % (sizeof(TELEM) * 8);
	TELEM tmp = 1;
	tmp <<= pos - 1;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] |= mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n <= 0 || n > BitLen) throw 2;
	int index = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[index] &= ~mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int index = GetMemIndex(n);
	TELEM tmp = (pMem[index] >> (n - 1));
	return tmp & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	//delete[] this->pMem;
	BitLen = bf.BitLen;
	pMem = new TELEM[BitLen];
	//MemLen = bf.MemLen;
	for (int i = 0; i < BitLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	bool check = true;
	for (int i = 0; i < this->BitLen; i++)
		if (this->pMem[i] != bf.pMem[i])
			check = false;
	return check;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int MinIndex = (BitLen < bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MinIndex; i++)
		pMem[i] |= bf.pMem[i];
	return *this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int MinIndex = (BitLen < bf.BitLen ? BitLen : bf.BitLen);
	for (int i = 0; i < MinIndex; i++)
		pMem[i] &= bf.pMem[i];
	return *this;
}

TBitField TBitField::operator~(void) // отрицание
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

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.MemLen; i++)
		istr >> bf.pMem[i];
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return ostr;
}
