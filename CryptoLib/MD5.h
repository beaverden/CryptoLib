#pragma once
#include "CryptoLib.h"
#include "utility.h"
#define MD5_LEN 32

/*
	@date 02.08.2017
	@author Denis Rozimovschii
	@purpose Calculates the MD5 hash using the standard implementation
	@documentation https://en.wikipedia.org/wiki/MD5

	@input  A buffer containing binary data and its length in bytes
	@output A 32-byte string where each subsequent 2 characters are of the form %02X, 
			meaning they represent in hex a padded 1-byte unsigned integer
*/

namespace CryptoLib
{
	CRYPTO_API char* MD5(void* buffer, size_t buffer_size);
	CRYPTO_API char* MD5FromFile(char* file_path);
}

