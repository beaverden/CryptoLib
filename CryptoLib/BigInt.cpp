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


// TO DO invalid numbers exceptions
BigInt::BigInt(std::string s)
{
	this->number = "";
	size_t off = 0;
	if (s[0] == '-')
	{
		this->number += '-';
		off++;
	}
	while (off < s.length() && s[off] == '0') off++;
	while (off < s.length())
	{
		if (s[off] >= '0' && s[off] <= '9') this->number += s[off];
		off++;
	}
	if (this->number == "-" || this->number == "") this->number = "0";
}

BigInt::BigInt(int64_t s)
{
	this->number = std::to_string(s);
}

size_t BigInt::GetLength() const 
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

bool BigInt::IsNegative() const
{
	return (this->number[0] == '-');
}

BigInt BigInt::Abs() const
{
	if (IsNegative())
	{
		return BigInt(this->number.substr(1, std::string::npos));
	}
	else
	{
		return BigInt(this->number);
	}
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

bool BigInt::operator==(const BigInt& other) const
{
	if (this->number.length() != other.GetLength()) return false;
	std::string otherString = other.GetValue();

	for (size_t i = 0; i < this->number.length(); i++)
	{
		if (this->number[i] != otherString[i]) return false;
	}
	return true;
}

bool BigInt::operator!=(const BigInt& other) const
{
	return !((*this) == other);
}

bool BigInt::operator>(const BigInt& other) const
{
	bool fneg = this->IsNegative();
	bool sneg = other.IsNegative();
	if (fneg == true && sneg == false) return false;
	if (fneg == false && sneg == true) return true;
	bool flip = fneg & sneg;

	if (this->number.length() > other.GetLength()) return ((flip) ? false : true);
	if (this->number.length() < other.GetLength()) return ((flip) ? true  : false);

	std::string otherString = other.GetValue();
	for (size_t i = 0; i < this->number.length(); i++)
	{
		if (this->number[i] > otherString[i]) return ((flip) ? false : true);
		if (this->number[i] < otherString[i]) return ((flip) ? true  : false);
	}
	return false;
}

bool BigInt::operator>=(const BigInt& other) const
{
	return ((*this) > other || (*this) == other);
}

bool BigInt::operator<(const BigInt& other) const
{
	return !((*this) > other) && !((*this) == other);
}

bool BigInt::operator<=(const BigInt& other) const
{
	return ((*this) < other || (*this) == other);
}


BigInt BigInt::operator+(const BigInt& other) const
{
	bool fneg = this->IsNegative();
	bool sneg = other.IsNegative();
	bool flip = fneg & sneg;

	if (fneg == true && sneg == false) return other - this->Abs();
	if (fneg == false && sneg == true) return (*this) - other.Abs();

	std::string a = this->number, b = other.number;
	if (a[0] == '-') a.erase(0, 1);
	if (b[0] == '-') b.erase(0, 1);
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
	if (flip) c = "-" + c;
	return BigInt(c);
}

BigInt BigInt::operator+(const int64_t &other) const
{
	BigInt big_other(other);
	return (*this) + big_other;
}

BigInt& BigInt::operator+=(const BigInt& other)
{
	(*this) = (*this) + other;
	return (*this);
}

BigInt& BigInt::operator+=(const int64_t other)
{
	(*this) = (*this) + other;
	return (*this);
}

BigInt BigInt::operator*(const BigInt& other) const
{
	
	std::string a = this->number;
	std::string b = other.GetValue();
	bool sign = this->IsNegative() ^ other.IsNegative();

	if (a[0] == '-') a.erase(0, 1);
	if (b[0] == '-') b.erase(0, 1);
	std::vector <uint8_t> res(a.length() + b.length() + 2);
	std::fill(res.begin(), res.end(), 0);

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	if (a.length()<b.length()) std::swap(a, b);
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
	if (sign) fin = '-' + fin;
	return BigInt(fin);
}

BigInt BigInt::operator*(const int64_t& other) const
{
	BigInt big_other(other);
	return (*this) * big_other;
}

BigInt& BigInt::operator*=(const BigInt& other)
{
	(*this) = (*this) * other;
	return (*this);
}

BigInt& BigInt::operator*=(const int64_t& other)
{
	(*this) = (*this) * other;
	return (*this);
}

BigInt BigInt::operator-() const
{
	if (this->IsNegative()) return this->Abs();
	return BigInt('-' + this->number);
}

BigInt BigInt::operator-(const BigInt& other) const
{
	bool fneg = this->IsNegative();
	bool sneg = other.IsNegative();
	
	
	if (fneg == true && sneg == false) return -((*this).Abs() + other.Abs());
	if (fneg == false && sneg == true) return (*this) + other.Abs();
	if (fneg == true && sneg == true) return other.Abs() - (*this).Abs();
	bool sign = ((*this) < other);
	
	std::string a = this->number, b = other.GetValue();
	if (a[0] == '-') a.erase(0, 1);
	if (b[0] == '-') b.erase(0, 1);
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	int borrow = 0, neg = 0;

	if (a<b) 
	{ 
		std::swap(a, b); 
	}
	std::string res;

	for (int i = 0; i < a.length(); i++) 
	{
		int x = a[a.length() - i - 1] - '0',
			y = b[a.length() - i - 1] - '0',
			z = 0;
		if (x - borrow < y) 
		{
			z = (10 + x - y - borrow);
			if (borrow == 0) borrow++;
		}
		else 
		{
			z = x - borrow - y;
			borrow = 0;
		}
		res += (char)(z + '0');
	}
	reverse(res.begin(), res.end());
	while (res.length() > 1 && res[0] == '0' ) res.erase(0, 1);
	if (sign) res = '-' + res;
	BigInt result(res);
	return result;
}

BigInt BigInt::operator-(const int64_t& other) const
{
	BigInt big_other(other);
	return (*this) - big_other;
}

BigInt& BigInt::operator-=(const BigInt& other)
{
	(*this) = (*this) - other;
	return (*this);
}

BigInt& BigInt::operator-=(const int64_t& other)
{
	(*this) = (*this) - other;
	return (*this);
}


BigInt BigInt::operator/(const BigInt& other) const
{
	if (other == 0) return BigInt(0);
	if ((*this).Abs() < other.Abs())
	{
		return BigInt(0);
	}
	BigInt abs_other = other.Abs();
	BigInt abs_this = (*this).Abs();
	BigInt l("1"), r = (*this).Abs(), last;
	while (l <= r) 
	{
		BigInt mid = l + r;
		mid = mid / 2;
		BigInt t = mid * abs_other;
		if (t <= abs_this)
		{
			last = mid;
			l = mid + 1;
		}
		else 
		{
			r = mid - 1;
		}
	}
	if ((*this).IsNegative() ^ other.IsNegative()) return -last;
	return last;
}

BigInt BigInt::operator/(const int64_t& other) const
{
	if (other == 0) return BigInt("0");

	std::string a = this->number;
	bool sign = this->IsNegative() ^ (other < 0);
	if (a[0] == '-') a.erase(0, 1);

	std::string res = "";
	int64_t val = abs(other), x = 0, k = 0;
	for (size_t i = 0; i<a.length(); i++) {
		int g = (a[i] - '0');
		if (g == 0 && x == 0) { res += "0"; continue; }
		x = x * 10 + g;
		if (x < val && k == 0 && i<a.length() - 1) continue;
		k = 1;
		res += std::to_string(x / val);
		x %= val;
	}
	while (res[0] == '0' && res.length()>1) res.erase(0, 1);
	if (sign) res = '-' + res;
	return BigInt(res);
}

BigInt& BigInt::operator/=(const BigInt& other)
{
	(*this) = (*this) / other;
	return (*this);
}

BigInt& BigInt::operator/=(const int64_t& other)
{
	(*this) = (*this) / other;
	return (*this);
}


BigInt BigInt::operator%(const BigInt& other) const
{
	BigInt div = (*this) / other;
	BigInt mod = (*this) - (div * other);
	return mod;
}

BigInt BigInt::operator%(const int64_t& other) const
{
	BigInt div_other(other);
	BigInt div = (*this) / div_other;
	BigInt mod = (*this) - (div * div_other);
	return mod;
}

BigInt& BigInt::operator%=(const BigInt& other)
{
	(*this) = (*this) % other;
	return (*this);
}

BigInt& BigInt::operator%=(const int64_t& other)
{
	(*this) = (*this) % other;
	return (*this);
}

void BigInt::swap(BigInt &a, BigInt &b)
{
	std::string temp = a.GetValue();
	a.SetValue(b.GetValue());
	b.SetValue(temp);
}