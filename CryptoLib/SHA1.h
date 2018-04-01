#pragma once
#include "utility.h"
#include "CryptoLib.h"
#define SHA1_LEN 40

/*
	@date 03.08.2017
	@author Denis Rozimovschii
	@purpose Calculates the SHA1 hash using the standard implementation
	@documentation https://en.wikipedia.org/wiki/SHA-1

	@input  A buffer containing binary data and its length in bytes
	@output A 40-byte string where each subsequent 2 characters are of the form %02X,
			meaning they represent in hex a padded 1-byte unsigned integer
*/

namespace CryptoLib
{
	CRYPTO_API char* SHA1(void* buffer, size_t buffer_size);
	CRYPTO_API char* SHA1FromFile(char* file_path);
}

