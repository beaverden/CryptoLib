// CryptoLib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ROT.h"
#include <string.h>
#include <time.h>
#include <string>
#include <sstream>
#include "BigInt.h"
#include "Primitives.h"

using namespace CryptoLib;
std::string GenerateRandomNumber(unsigned int length)
{
	std::string result = "";
	for (size_t i = 0; i < length; i++)
	{
		result += (char)((rand() % 10) + '0');
	}
	if (length == 0) return "0";
	if (rand() % 2) result = '-' + result;
	return result;
}

int main(int args, char* argv[])
{
	srand(time(0));
	for (size_t i = 0; i < 50; i++)
	{
		int alen = rand() % 2 + 1;
		int blen = rand() % 2 + 1;
		std::string sa = GenerateRandomNumber(alen);
		std::string sb = GenerateRandomNumber(blen);
		BigInt ba(sa);
		BigInt bb(sb);
		Primitives::Vector2D res;
		BigInt gcd;
		res = Primitives::ExtendedGCD(ba, bb, &gcd);
		BigInt val = res.alpha * ba + res.beta * bb;
	}

	return 0;
}

