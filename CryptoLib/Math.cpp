#include "stdafx.h"
#include "Math.h"
#include <algorithm>

std::string CryptoLib::Math::MultiplyGridMethod(std::string a, std::string b)
{
	int res[10000] = { 0 }, shift = 0;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	if (a.length()<b.length()) swap(a, b);
	int lenA = a.length(),
		lenB = b.length(),
		finlen = 0;

	for (int i = 0; i<lenB; i++) {
		int rem = 0, z = shift;
		for (int j = 0; j<lenA; j++) {
			int x = b[i] - '0',
				y = a[j] - '0';
			int prod = x*y + rem + res[z];
			res[z] = prod % 10;
			rem = prod / 10;
			z++;
		}
		finlen = std::max(finlen, --z);
		while (rem>0) {
			int newLen = z++;
			res[z] += rem;
			rem = res[z] / 10;
			res[z] %= 10;
			finlen = std::max(finlen, z);
		}
		shift++;
	}
	std::string fin;
	for (int i = finlen; i >= 0; i--) fin += (char)(res[i] + '0');
	while (fin[0] == '0' && fin.length()>1) fin.erase(0, 1);
	return fin;
}