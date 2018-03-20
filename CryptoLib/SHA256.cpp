#include "stdafx.h"
#include "SHA256.h"

#include <stdint.h>

static uint32_t K_table[]
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

char* CryptoLib::SHA256(void* buffer, size_t buffer_size)
{
	uint32_t h0 = 0x6a09e667;
	uint32_t h1 = 0xbb67ae85;
	uint32_t h2 = 0x3c6ef372;
	uint32_t h3 = 0xa54ff53a;
	uint32_t h4 = 0x510e527f;
	uint32_t h5 = 0x9b05688c;
	uint32_t h6 = 0x1f83d9ab;
	uint32_t h7 = 0x5be0cd19;

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
	uint32_t* block_words = new uint32_t[64];

	for (size_t block_id = 0; block_id < blocks_count; block_id++)
	{
		uint32_t* start = (uint32_t*)(working_buffer + (block_id << 6));
		for (size_t i = 0; i < 16; i++)
		{
			block_words[i] = REVERSE_32(start[i]);
		}
		for (size_t i = 16; i < 64; i++)
		{
			uint32_t s0 = RIGHT_ROTATE(block_words[i - 15], 7) ^ RIGHT_ROTATE(block_words[i - 15], 18) ^ (block_words[i - 15] >> 3);
			uint32_t s1 = RIGHT_ROTATE(block_words[i - 2], 17) ^ RIGHT_ROTATE(block_words[i - 2],  19) ^ (block_words[i - 2] >> 10);
			block_words[i] = block_words[i - 16] + s0 + block_words[i - 7] + s1;
		}

		uint32_t a = h0;
		uint32_t b = h1;
		uint32_t c = h2;
		uint32_t d = h3;
		uint32_t e = h4;
		uint32_t f = h5; 
		uint32_t g = h6;
		uint32_t h = h7;

		for (size_t i = 0; i < 64; i++)
		{
			uint32_t S1 = RIGHT_ROTATE(e, 6) ^ RIGHT_ROTATE(e, 11) ^ RIGHT_ROTATE(e, 25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = h + S1 + ch + K_table[i] + block_words[i];
			uint32_t S0 = RIGHT_ROTATE(a, 2) ^ RIGHT_ROTATE(a, 13) ^ RIGHT_ROTATE(a, 22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = S0 + maj;
		
			h = g;
			g = f;
			f = e;
			e = d + temp1;
			d = c;
			c = b;
			b = a;
			a = temp1 + temp2;
		}
		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;
		h4 += e;
		h5 += f;
		h6 += g;
		h7 += h;
	}

	char* output = new char[SHA256_LEN + 1];
	char* iterator = output;
	uint32_t values[] = { h0, h1, h2, h3, h4, h5, h6, h7 };

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			sprintf(iterator, "%02x", (values[i] & 0xFF000000) >> 24);
			values[i] <<= 8;
			iterator += 2;
		}
	}
	output[SHA256_LEN] = NULL;

	delete[] block_words;
	delete[] working_buffer;
	return output;
}

char* CryptoLib::SHA256FromFile(char* file_path)
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

	char* result = CryptoLib::SHA256(buffer, size);
	delete[] buffer;
	return result;
}