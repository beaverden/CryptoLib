#pragma once
#include "BigInt.h"

namespace CryptoLib
{
	namespace Primitives
	{
		__declspec(dllexport) struct Vector2D
		{
			BigInt alpha;
			BigInt beta;
			Vector2D() : alpha(0), beta(0) {}
			Vector2D(BigInt _alpha, BigInt _beta) : alpha(_alpha), beta(_beta) {}
			Vector2D operator+(const Vector2D& other);
			Vector2D operator-(const Vector2D& other);
			Vector2D operator*(const BigInt& other);
		};

		__declspec(dllexport) BigInt POW(_In_ const BigInt &num, _In_ const BigInt &power);
		__declspec(dllexport) BigInt GCD(_In_ const BigInt &a, _In_ const BigInt &b);
		__declspec(dllexport) Vector2D ExtendedGCD(_In_ const BigInt &a, _In_ const BigInt &b, _Out_opt_ BigInt* gcd_result = nullptr);
	}
}