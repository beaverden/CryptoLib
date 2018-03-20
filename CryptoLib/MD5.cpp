#include "stdafx.h"
#include "MD5.h"
#include <stdint.h>

static const uint32_t START_A = 0x67452301;
static const uint32_t START_B = 0xEFCDAB89;
static const uint32_t START_C = 0x98BADCFE;
static const uint32_t START_D = 0x10325476;

// The binary integer part of the sines of integers (Radians) as constants:
static uint32_t K_table[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

static uint8_t rotate_amounts[] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
};


char* CryptoLib::MD5(void* buffer, size_t buffer_size)
{
	uint32_t a0 = START_A;
	uint32_t b0 = START_B;
	uint32_t c0 = START_C;
	uint32_t d0 = START_D;

	size_t starting_length = buffer_size * BYTE_SIZE;
	size_t padded_length = NEAREST_512_MULTIPLE(starting_length + 1);
	if (padded_length - (starting_length + 1) < SIZE_INT_64)
	{
		padded_length = NEAREST_512_MULTIPLE(padded_length + 1);
	}
	
	size_t padded_len_bytes = padded_length >> 3;
	uint8_t* working_buffer = new uint8_t[padded_len_bytes];

	memset(working_buffer, 0x00, padded_len_bytes);
	memcpy(working_buffer, buffer, buffer_size);

	working_buffer[buffer_size] = 0x80; // first append 1 bit
	uint64_t length_in_bits = (uint64_t)starting_length;

	uint64_t* length_assign = (uint64_t*)(working_buffer + padded_len_bytes - sizeof(uint64_t));
	(*length_assign) = length_in_bits;

	size_t blocks_count = padded_len_bytes >> 6;
	for (size_t block_id = 0; block_id < blocks_count; block_id++)
	{
		uint32_t* block_words = (uint32_t*)(working_buffer + (block_id << 6));
		
		uint32_t A = a0;
		uint32_t B = b0;
		uint32_t C = c0;
		uint32_t D = d0;
		for (size_t i = 0; i < 64; i++)
		{
			uint32_t F, g;
			if (i < 16)
			{
				F = (B & C) | ((~B) & D);
				g = i;
			}
			else if (i < 32)
			{
				F = (D & B) | ((~D) & C);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48)
			{
				F = B ^ C ^ D;
				g = (3 * i + 5) % 16;
			}
			else
			{
				F = C ^ (B | (~D));
				g = (7 * i) % 16;
			}
			F += A + K_table[i] + block_words[g];
			A = D;
			D = C;
			C = B;
			B += LEFT_ROTATE(F, rotate_amounts[i]);
		}
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}
		
	char* output = new char[MD5_LEN + 1];
	char* iterator = output;
	uint32_t values[] = { a0, b0, c0, d0 };

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			sprintf(iterator, "%02x", values[i] & 0xFF);
			values[i] >>= 8;
			iterator += 2;
		}
	}
	output[MD5_LEN] = NULL;

	delete[] working_buffer;
	return output;
}

char* CryptoLib::MD5FromFile(char* file_path)
{
	FILE* f = fopen(file_path, "rb+");
	if (f == nullptr)
	{
		return NULL;
	}
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* buffer = new char[size];
	fread(buffer, sizeof(unsigned char), size, f);

	char* result = CryptoLib::MD5(buffer, size);
	delete[] buffer;
	return result;
}