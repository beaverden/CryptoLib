#pragma once
#include "CryptoLib.h"

namespace CryptoLib {
	namespace ROT {
		namespace ROT_ALPHABET
		{
			static unsigned char* LETTERS_ALPHABET = (unsigned char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
			static unsigned int	LETTERS_ALPHABET_LEN = 52;

			static unsigned char* SMALL_LETTERS_ALPHABET = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
			static unsigned int	SMALL_LETTERS_ALPHABET_LEN = 26;

			static unsigned char* BIG_LETTERS_ALPHABET = (unsigned char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
			static unsigned int	BIG_LETTERS_ALPHABET_LEN = 26;
		}


		#define NUMBERS					(unsigned char*)"012345689"
		#define NUMBERS_SIZE			10

		#define ALPHANUMERIC			(unsigned char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
		#define ALPHANUMERIC_SIZE		62

		#define PRINTABLE_ALPHABET		(unsigned char*)"!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"
		#define PRINTABLE_ALPHABET_SIZE	94

		#define MAX_ALPHABET_LEN		1 << 8

		// Rotations can be negative, in this case it will be backwards
		// It will ignore characters not present in the ALPHABET
		CRYPTO_API void ROT(
			void* input,
			size_t input_size,
			void* output,
			size_t output_size,
			void* alphabet,
			unsigned char alphabet_size,
			int rotations
		);
	}
}