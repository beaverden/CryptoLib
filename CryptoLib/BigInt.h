#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <algorithm>

namespace CryptoLib
{
	class _declspec(dllexport) BigInt
	{
	public:
		BigInt();
		BigInt(std::string s);
		BigInt(uint64_t s);

		size_t GetLength();
		std::string GetValue() const;
		void SetValue(std::string newValue);

		std::ostream& operator<<(std::ostream& output);
		std::string& operator<<(std::string& output);

		BigInt& operator=(const BigInt& other);

		BigInt operator+(const BigInt& other) const;
		BigInt operator+(const uint64_t& other) const;
		BigInt& operator+=(const BigInt& other);
		BigInt& operator+=(const uint64_t other);

		BigInt operator*(const BigInt& other) const;
		BigInt operator*(const uint64_t& other) const;
		BigInt& operator*=(const BigInt& other);
		BigInt& operator*=(const uint64_t& other);

		~BigInt();
	private:
		std::string number;
	};


}


