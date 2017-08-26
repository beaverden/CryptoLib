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
	//srand(time(0));
	size_t i = 0;
	Primitives::POWModM(BigInt("93440596342887581257"), BigInt("44"), BigInt("-429"));

	while (i < 50)
	{
		int alen = rand() % 2 + 1;
		int blen = rand() % 2 + 1;
		std::string sa = GenerateRandomNumber(alen);
		std::string sb = GenerateRandomNumber(blen);
		BigInt ba(sa);
		BigInt bb(sb);


		if (Primitives::GCD(ba, bb) == 1)
		{
			i++;
		}
		else continue;
		if (ba == -4)
		{
			int j = 0;
		}
		char msg[10000] = { 0 };
		BigInt res = Primitives::MathematicalModulo((Primitives::InverseModM(ba, bb) * ba), bb);
		printf("%s\n    %s\n    %s\n", ba.GetValue().c_str(), bb.GetValue().c_str(), res.GetValue().c_str());
		if (res != 1)
		{
			int j = 0;
		}
	}

	return 0;
}

