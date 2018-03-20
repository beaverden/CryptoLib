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

BigInt Primitives::POWModM(_In_ const BigInt &_num, _In_ const BigInt &_power, _In_ const BigInt &m)
{
	BigInt result = 1;
	BigInt power = _power;
	BigInt num = _num;
	while (power > 0)
	{
		if (power % 2 != 0)
		{
			result = (result * num) % m;
		}
		power /= 2;
		num = (num * num) % m;
	}
	return result;

}

BigInt Primitives::MathematicalModulo(const BigInt& a, const BigInt& b)
{
	BigInt res = a % b;
	if (res < 0) return res + b.Abs();
	return res;
}

Vector2D Primitives::ExtendedGCD(const BigInt &_a, const BigInt &_b, BigInt* gcd_result)
{
	bool flipa = _a.IsNegative();
	bool flipb = _b.IsNegative();
	BigInt a = _a.Abs();
	BigInt b = _b.Abs();
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
	if (flipa) va.alpha = -va.alpha;
	if (flipb) va.beta = -va.beta;

	if (gcd_result != nullptr)
	{
		(*gcd_result) = a;
	}
	return va;
}

BigInt Primitives::InverseModM(const BigInt &a, const BigInt &m)
{
	Vector2D gcd_result = Primitives::ExtendedGCD(a, -m);
	return gcd_result.alpha;
}