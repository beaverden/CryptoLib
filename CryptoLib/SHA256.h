#pragma once
#include "utility.h"
#include "CryptoLib.h"
#define SHA256_LEN 64

/*
	@date 04.08.2017
	@author Denis Rozimovschii
	@purpose Calculates the SHA-2 hash using the standard implementation
	@documentation https://en.wikipedia.org/wiki/SHA-2

	@input  A buffer containing binary data and its length in bytes
	@output A 64-byte string where each subsequent 2 characters are of the form %02X,
	meaning they represent in hex a padded 1-byte unsigned integer
*/

namespace CryptoLib
{
	CRYPTO_API char* SHA256(void* buffer, size_t buffer_size);
	CRYPTO_API char* SHA256FromFile(char* file_path);
}