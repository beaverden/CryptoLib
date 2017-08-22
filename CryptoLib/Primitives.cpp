#include "stdafx.h"
#include "Primitives.h"


using namespace CryptoLib;
using namespace CryptoLib::Primitives;

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D(this->alpha + other.alpha, this->beta + other.beta);
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	return Vector2D(this->alpha - other.alpha, this->beta - other.beta);
}
Vector2D Vector2D::operator*(const BigInt& other)
{
	return Vector2D(this->alpha * other, this->beta * other);
}

BigInt Primitives::GCD(const BigInt& a, const BigInt& b)
{
	BigInt _a = a;
	BigInt _b = b;

	while (_b != 0)
	{
		BigInt temp = (_a) % (_b);
		_a = _b;
		_b = temp;
	}
	return _a;
}

BigInt Primitives::POW(const BigInt& _num, const BigInt& _power)
{
	BigInt result = 1;
	BigInt power = _power;
	BigInt num = _num;
	while (power > 0)
	{
		if (power % 2 != 0)
		{
			result *= num;
		}
		power /= 2;
		num *= num;	
	}
	return result;
}

Vector2D Primitives::ExtendedGCD(const BigInt &_a, const BigInt &_b, BigInt* gcd_result)
{
	BigInt a = _a;
	BigInt b = _b;
	BigInt temp;
	Vector2D va(1, 0);
	Vector2D vb(0, 1);
	Vector2D vtemp;

	while (b != 0)
	{
		temp = (a) % (b);
		vtemp = va - (vb * (a / b));
		a = b;
		b = temp;
		va = vb;
		vb = vtemp;
	}
	if (gcd_result != nullptr)
	{
		(*gcd_result) = a;
	}
	return va;
}