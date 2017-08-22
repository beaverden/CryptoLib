#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <algorithm>

/*
	@author Denis Rozimovschii
	@date 08-07-2017
	@purpose Arithmetic with long numbers
	@operations: 
		addition (tested)
		substraction (tested)
		multiplication (tested)
		comparisons (tested)
		division by 64 bit integer (tested)
		division by arbitrary length integer (tested)

	@input unsigned integers of arbitrary length

	Warning: the library operates with unsigned integers
			 of arbitrary length. The substraction operand
			 will return the absoulte value of the difference,
			 as well as other
*/

namespace CryptoLib
{
	class _declspec(dllexport) BigInt
	{
	public:
		BigInt();
		BigInt(std::string s);
		BigInt(int64_t s);

		size_t GetLength() const;
		std::string GetValue() const;
		void SetValue(std::string newValue);
		bool IsNegative() const;
		BigInt Abs() const;

		std::ostream& operator<<(std::ostream& output);
		std::string& operator<<(std::string& output);

		BigInt& operator=(const BigInt& other);

		bool operator==(const BigInt& other) const;
		bool operator!=(const BigInt& other) const;
		bool operator>(const BigInt& other) const;
		bool operator>=(const BigInt& other) const;
		bool operator<(const BigInt& other) const;
		bool operator<=(const BigInt& other) const;

		BigInt operator+(const BigInt& other) const;
		BigInt operator+(const int64_t& other) const;
		BigInt& operator+=(const BigInt& other);
		BigInt& operator+=(const int64_t other);

		BigInt operator*(const BigInt& other) const;
		BigInt operator*(const int64_t& other) const;
		BigInt& operator*=(const BigInt& other);
		BigInt& operator*=(const int64_t& other);

		BigInt operator-(const BigInt& other) const;
		BigInt operator-(const int64_t& other) const;
		BigInt& operator-=(const BigInt& other);
		BigInt& operator-=(const int64_t& other);

		BigInt operator-() const;
		BigInt operator/(const BigInt& other) const;
		BigInt operator/(const int64_t& other) const;
		BigInt& operator/=(const BigInt& other);
		BigInt& operator/=(const int64_t& other);

		BigInt operator%(const BigInt& other) const;
		BigInt operator%(const int64_t& other) const;
		BigInt& operator%=(const BigInt& other);
		BigInt& operator%=(const int64_t& other);

		static void swap(BigInt& a, BigInt& b);

		~BigInt();
	private:
		std::string number;
	};


}


