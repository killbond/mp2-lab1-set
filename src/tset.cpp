// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	this->MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	this->MaxPower = s.BitField.GetLength();
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return BitField.GetLength();
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem) == 1) return 1;
	return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	this->MaxPower = s.MaxPower;
	this->BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (this->BitField == s.BitField) return 1;
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !operator==(s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet set(*this);
	set.BitField = set.BitField | s.BitField;
	return set;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet set(*this);
	set.InsElem(Elem);
	return set;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet set(*this);
	set.DelElem(Elem);
	return set;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet set(*this);
	set.BitField = set.BitField & s.BitField;
	return set;
}

TSet TSet::operator~(void) // дополнение
{
	TSet set(1);
	for (int i = 0; i < set.BitField.GetLength(); i++)
		if (!this->BitField.GetBit(i))
			set.BitField.SetBit(i);
	return set;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	char temp;
	int value = -1;
	int index = 0;
	while (istr.get(temp))
	{
		if (temp == '\n')
		{
			s.InsElem(value);
			break;
		}
		if (temp == ' ' && value == -1)
			continue;
		if (temp == ' ')
		{
			s.InsElem(value);
			value = -1;
			index = 0;
			continue;
		}
		if (value == -1)
			value = 0;
		value = value * 10 + ((int)temp - 48);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{

	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		ostr << i << endl;
	}
	return ostr;
}
