#include "stdafx.h"
#include "BigInt.h"

using namespace CryptoLib;

BigInt::BigInt()
{
	this->number = "0";
}

BigInt::~BigInt()
{
}

BigInt::BigInt(std::string s)
{
	this->number = s;
}

BigInt::BigInt(uint64_t s)
{
	this->number = std::to_string(s);
}

size_t BigInt::GetLength()
{
	return this->number.length();
}

std::string BigInt::GetValue() const
{
	return this->number;
}

void BigInt::SetValue(std::string newValue)
{
	this->number = newValue;
}

std::ostream& BigInt::operator<<(std::ostream& output)
{
	output << this->number;
	return output;
}

std::string& BigInt::operator<<(std::string& output)
{
	output = this->number;
	return output;
}

BigInt& BigInt::operator=(const BigInt& other)
{
	if (this != &other)
	{
		this->number = other.GetValue();
	}
	return *this;
}

BigInt BigInt::operator+(const BigInt& other) const
{
	std::string a = this->number, b = other.number;
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	std::string c;
	int r = 0, t;
	for (int i = 0; i<a.length(); i++) 
	{
		int x = (a[a.length() - i - 1] - '0'),
			y = (b[a.length() - i - 1] - '0');
		t = x + y + r;
		c += (char)((t % 10) + '0');
		r = t / 10;
	}
	if (r != 0) c += (char)(r + '0');
	reverse(c.begin(), c.end());
	return BigInt(c);
}

BigInt BigInt::operator+(const uint64_t &other) const
{
	BigInt big_other(other);
	return (*this) + big_other;
}

BigInt& BigInt::operator+=(const BigInt& other)
{
	(*this) = (*this) + other;
	return (*this);
}

BigInt& BigInt::operator+=(const uint64_t other)
{
	(*this) = (*this) + other;
	return (*this);
}

BigInt BigInt::operator*(const BigInt& other) const
{
	std::string a = this->number;
	std::string b = other.GetValue();
	std::vector <uint8_t> res(a.length() + b.length() + 2);
	std::fill(res.begin(), res.end(), 0);

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	if (a.length()<b.length()) swap(a, b);
	size_t lenA = a.length(),
		   lenB = b.length(),
		   finlen = 0;
	for (size_t i = 0; i<lenB; i++) 
	{
		uint8_t rem = 0;
		for (size_t j = 0; j<lenA; j++)
		{
			uint8_t x = b[i] - '0',
					y = a[j] - '0';
			int prod = x*y + rem + res[i+j];
			res[i+j] = prod % 10;
			rem = prod / 10;
		}
		if (rem > 0)
		{
			res[i + lenA] = (res[i + lenA] + rem) % 10;
		}
	}

	std::string fin = "";
	for (int i = lenA + lenB + 1; i >= 0; i--)
	{
		fin += (char)(res[i] + '0');
	}
	while (fin.length() > 1 && fin[0] == '0' ) fin.erase(0, 1);
	return BigInt(fin);
}

BigInt BigInt::operator*(const uint64_t& other) const
{
	BigInt big_other(other);
	return (*this) * big_other;
}

BigInt& BigInt::operator*=(const BigInt& other)
{
	(*this) = (*this) * other;
	return (*this);
}

BigInt& BigInt::operator*=(const uint64_t& other)
{
	(*this) = (*this) * other;
	return (*this);
}