#include "stdafx.h"
#include "ROT.h"

#define CHAR_DEREF(buffer, index)\
	(*(unsigned char*)((unsigned int)(buffer) + (index)))

void ROT(
	void* input,
	size_t input_size,
	void* output,
	size_t output_size,
	void* alphabet,
	unsigned char alphabet_size,
	int rotations
)
{
	bool present_in_alphabet[MAX_ALPHABET_LEN] = { false };
	unsigned char alphabet_positions[MAX_ALPHABET_LEN] = { 0 };
	for (size_t i = 0; i < alphabet_size; i++)
	{
		present_in_alphabet[CHAR_DEREF(alphabet, i)] = true;
		alphabet_positions[CHAR_DEREF(alphabet, i)] = (unsigned char)i;
	}
	rotations = rotations % (int)alphabet_size;
	for (size_t i = 0; i < input_size; i++)
	{
		if (!present_in_alphabet[CHAR_DEREF(input, i)])
		{
			CHAR_DEREF(output, i) = CHAR_DEREF(input, i);
		}
		else
		{
			unsigned char position = alphabet_positions[CHAR_DEREF(input, i)];
			int next = (position + rotations) % alphabet_size;
			if (next < 0) next += alphabet_size;
			CHAR_DEREF(output, i) = CHAR_DEREF(alphabet, next);
		}
		
	}
}

void FrequencyAttack_ROT_English(
	unsigned char* ciphertext,
	unsigned int ciphertext_size,
	unsigned char* plain_text,
	unsigned int plain_text_size
)
{
	const char* frequency = "etaoinshrdlcumwfgypbvkjxqz";
}