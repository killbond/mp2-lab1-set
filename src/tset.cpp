// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tset.cpp - Copyright (c) ������� �.�. 04.10.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ��������� - ���������� ����� ������� ����

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	this->MaxPower = mp;
}

// ����������� �����������
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	this->MaxPower = s.BitField.GetLength();
}

// ����������� �������������� ����
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return this->BitField;
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
	return BitField.GetLength();
}

int TSet::IsMember(const int Elem) const // ������� ���������?
{
	if (BitField.GetBit(Elem) == 1) return 1;
	return 0;
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
	BitField.ClrBit(Elem);
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet &s) // ������������
{
	this->MaxPower = s.MaxPower;
	this->BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // ���������
{
	if (this->BitField == s.BitField) return 1;
	return 0;
}

int TSet::operator!=(const TSet &s) const // ���������
{
	return !operator==(s);
}

TSet TSet::operator+(const TSet &s) // �����������
{
	TSet set(*this);
	set.BitField = set.BitField | s.BitField;
	return set;
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
	TSet set(*this);
	set.InsElem(Elem);
	return set;
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
	TSet set(*this);
	set.DelElem(Elem);
	return set;
}

TSet TSet::operator*(const TSet &s) // �����������
{
	TSet set(*this);
	set.BitField = set.BitField & s.BitField;
	return set;
}

TSet TSet::operator~(void) // ����������
{
	TSet set(1);
	for (int i = 0; i < set.BitField.GetLength(); i++)
		if (!this->BitField.GetBit(i))
			set.BitField.SetBit(i);
	return set;
}

// ���������� �����/������

istream &operator>>(istream &istr, TSet &s) // ����
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

ostream& operator<<(ostream &ostr, const TSet &s) // �����
{

	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		ostr << i << endl;
	}
	return ostr;
}
