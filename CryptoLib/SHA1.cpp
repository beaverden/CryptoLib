#include "stdafx.h"
#include "SHA1.h"
#include <stdint.h>


char* CryptoLib::SHA1(void* buffer, size_t buffer_size)
{
	uint32_t h0 = 0x67452301;
	uint32_t h1 = 0xEFCDAB89;
	uint32_t h2 = 0x98BADCFE;
	uint32_t h3 = 0x10325476;
	uint32_t h4 = 0xC3D2E1F0;

	uint64_t starting_length = (uint64_t)buffer_size * BYTE_SIZE;
	uint64_t padded_length = NEAREST_512_MULTIPLE(starting_length + 1);
	if (padded_length - (starting_length + 1) < SIZE_INT_64)
	{
		padded_length = NEAREST_512_MULTIPLE(padded_length + 1);
	}

	uint64_t padded_len_bytes = padded_length >> 3;
	uint8_t* working_buffer = new uint8_t[padded_len_bytes];

	memset(working_buffer, 0x00, padded_len_bytes);
	memcpy(working_buffer, buffer, buffer_size);

	working_buffer[buffer_size] = 0x80; // first append 1 bit
	uint64_t length_in_bits = (uint64_t)starting_length;

	uint64_t* length_assign = (uint64_t*)(working_buffer + padded_len_bytes - sizeof(uint64_t));
	(*length_assign) = REVERSE_64(length_in_bits);


	uint64_t blocks_count = padded_len_bytes >> 6;
	uint32_t* block_words = new uint32_t[80];

	for (size_t block_id = 0; block_id < blocks_count; block_id++)
	{
		uint32_t* start = (uint32_t*)(working_buffer + (block_id << 6));
		for (size_t i = 0; i < 16; i++)
		{
			block_words[i] = REVERSE_32(start[i]);
		}
		for (size_t i = 16; i < 80; i++)
		{
			block_words[i] = (block_words[i - 3] ^ block_words[i - 8] ^ block_words[i - 14] ^ block_words[i - 16]);
			block_words[i] = LEFT_ROTATE(block_words[i], 1);
		}

		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;
		uint32_t e = h4;
		uint32_t f, k;
		for (size_t i = 0; i < 80; i++)
		{
			if (i < 20)
			{
				f = (b & c) | ((~b) & d);
				k = 0x5A827999;
			}
			else if (i < 40)
			{
				f = b ^ c ^ d;
				k = 0x6ED9EBA1;
			}
			else if (i < 60)
			{
				f = (b & c) | (b & d) | (c & d);
				k = 0x8F1BBCDC;
			}
			else
			{
				f = b ^ c ^ d;
				k = 0xCA62C1D6;
			}

			uint32_t temp = LEFT_ROTATE(a, 5) + f + e + k + block_words[i];
			e = d;
			d = c;
			c = LEFT_ROTATE(b, 30);
			b = a;
			a = temp;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		h4 += e;
	}

	char* output = new char[SHA1_LEN + 1];
	char* iterator = output;
	uint32_t values[] = { h0, h1, h2, h3, h4 };

	for (size_t i = 0; i < 5; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			sprintf(iterator, "%02x", (values[i] & 0xFF000000) >> 24);
			values[i] <<= 8;
			iterator += 2;
		}
	}
	output[SHA1_LEN] = NULL;

	delete[] block_words;
	delete[] working_buffer;
	return output;
}

char* CryptoLib::SHA1FromFile(char* file_path)
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

	char* result = CryptoLib::SHA1(buffer, size);
	delete[] buffer;
	return result;
}