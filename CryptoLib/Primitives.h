#pragma once
#include "BigInt.h"
#include "CryptoLib.h"

namespace CryptoLib
{
	namespace Primitives
	{
		CRYPTO_API struct Vector2D
		{
			BigInt alpha;
			BigInt beta;
			Vector2D() : alpha(0), beta(0) {}
			Vector2D(BigInt _alpha, BigInt _beta) : alpha(_alpha), beta(_beta) {}
			Vector2D operator+(const Vector2D& other);
			Vector2D operator-(const Vector2D& other);
			Vector2D operator*(const BigInt& other);
		};

		CRYPTO_API BigInt POW(_In_ const BigInt &num, _In_ const BigInt &power);
		CRYPTO_API BigInt POWModM(_In_ const BigInt &num, _In_ const BigInt &power, _In_ const BigInt &m);
		CRYPTO_API BigInt MathematicalModulo(const BigInt& a, const BigInt& b);
		CRYPTO_API BigInt GCD(_In_ const BigInt &a, _In_ const BigInt &b);
		CRYPTO_API Vector2D ExtendedGCD(_In_ const BigInt &a, _In_ const BigInt &b, _Out_opt_ BigInt* gcd_result = nullptr);
		CRYPTO_API BigInt InverseModM(_In_ const BigInt &a, _In_ const BigInt &m);
	}
}