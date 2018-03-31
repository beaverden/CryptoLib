#include "stdafx.h"
#include "DES.h"

void CryptoLib::DES::DesKeySchedule(
	uint64_t key, 
	KEY_SET* key_set
) 
{
	uint64_t permuted_key = 0;
	PERMUTE(key, permuted_key, DES::PC1, 56); 
	uint64_t Cn = (permuted_key & FIRST_28_BIT);
	uint64_t Dn = (permuted_key  & SECOND_28_BIT) << 28;
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < KEY_LSHIFT[i]; j++) {
			LSHIFT(Cn);
			LSHIFT(Dn);
		}
		uint64_t combined = (Cn | (Dn >> 28));
		uint64_t Kn = 0;
		PERMUTE(combined, Kn, DES::PC2, 48); 
		key_set->keys[i] = Kn;
	}
}

uint64_t get_shifted(uint64_t perm, uint64_t group_id)
{
	uint64_t group = (perm & (FIRST_6_BIT >> (group_id * 6))) >> (64 - (group_id+1) * 6);
	uint64_t row = ((group & BIT_NO_6) >> 4) | (group & BIT_NO_1);
	uint64_t column = (group & BIT_NO_2345) >> 1;
	uint64_t index = row * 16 + column;
	return CryptoLib::DES::REF_BOX[group_id][index];
}

uint64_t CryptoLib::DES::Feistel(uint64_t Rn, uint64_t Kn)
{
	uint64_t permutation = 0;
	PERMUTE(Rn, permutation, DES::E, 48); 
	permutation ^= Kn;

	uint64_t substitute =
		get_shifted(permutation, 0) << 28 |
		get_shifted(permutation, 1) << 24 |
		get_shifted(permutation, 2) << 20 |
		get_shifted(permutation, 3) << 16 |
		get_shifted(permutation, 4) << 12 |
		get_shifted(permutation, 5) << 8  |
		get_shifted(permutation, 6) << 4  |
		get_shifted(permutation, 7) << 0;
	substitute <<= 32;
	uint64_t permuted_result = 0;
	PERMUTE(substitute, permuted_result, DES::P, 32); 
	return permuted_result;
}



void CryptoLib::DES::DesEncryptBlock(
	uint64_t message,
	uint64_t key,
	uint64_t* result
)
{
	DES::KEY_SET key_set;
	DES::DesKeySchedule(key, &key_set);
	uint64_t initial_permutation = 0;
	PERMUTE(message, initial_permutation, DES::IP, 64); 
	uint64_t Ln = (initial_permutation & FIRST_32_BIT);
	uint64_t Rn = ((initial_permutation & SECOND_32_BIT) << 32);
	for (int i = 0; i < 16; i++) 
	{
		uint64_t Ln_next = Rn;
		uint64_t Rn_next = Ln ^ Feistel(Rn, key_set.keys[i]);
		Ln = Ln_next;
		Rn = Rn_next;
	}
	uint64_t reversed = Rn | (Ln >> 32);
	uint64_t permuted = 0;
	PERMUTE(reversed, permuted, DES::IP2, 64); 
	(*result) = permuted;
}

void CryptoLib::DES::DesDecryptBlock(
	uint64_t message,
	uint64_t key,
	uint64_t* result
)
{
	DES::KEY_SET key_set;
	DES::DesKeySchedule(key, &key_set);
	uint64_t initial_permutation = 0;
	PERMUTE(message, initial_permutation, DES::IP, 64); 
	uint64_t Ln = (initial_permutation & FIRST_32_BIT);
	uint64_t Rn = ((initial_permutation & SECOND_32_BIT) << 32);
	for (int i = 15; i >= 0; i--)
	{
		uint64_t Ln_next = Rn;
		uint64_t Rn_next = Ln ^ Feistel(Rn, key_set.keys[i]);
		Ln = Ln_next;
		Rn = Rn_next;
	}
	uint64_t reversed = Rn | (Ln >> 32);
	uint64_t permuted = 0;
	PERMUTE(reversed, permuted, DES::IP2, 64); 
	(*result) = permuted;
}

void CryptoLib::DES::DesEncrypt(
	uint64_t* message,
	size_t message_length,
	uint64_t* ciphertext,
	uint64_t key
)
{
	for (size_t i = 0; i < message_length / sizeof(uint64_t); i++)
	{
		DES::DesEncryptBlock(message[i], key, &ciphertext[i]);
	}
}

void CryptoLib::DES::DesDecrypt(
	uint64_t* ciphertext,
	size_t ciphertext_length,
	uint64_t* message,
	uint64_t key
)
{
	for (size_t i = 0; i < ciphertext_length / sizeof(uint64_t); i++)
	{
		DES::DesDecryptBlock(ciphertext[i], key, &message[i]);
	}
}

bool CryptoLib::DES::MITMAttack(
	uint64_t known_key1,
	uint64_t known_key2,
	uint64_t* plaintext,
	uint64_t* ciphertext,
	size_t text_size,
	uint64_t* result_key1,
	uint64_t* result_key2
)
{
	std::map<std::string, uint64_t> pairs;
	uint64_t* result = new uint64_t[text_size / sizeof(uint64_t)];
	for (int i = 0; i < 256; i++)
	{
		uint64_t full_key1 = known_key1;
		for (int j = 56; j < 64; j++)
		{
			if (i & (0x01 << (63 - j)))
			{
				SET(full_key1, j);
			}
		}
		DES::DesEncrypt(plaintext, text_size, result, full_key1);
		std::string hash = CryptoLib::MD5(result, text_size);
		pairs[hash] = full_key1;
	}

	for (int i = 0; i < 256; i++)
	{
		uint64_t full_key2 = known_key2;
		for (int j = 56; j < 64; j++)
		{
			if (i & (0x01 << (63 - j)))
			{
				SET(full_key2, j);
			}
		}
		DES::DesDecrypt(ciphertext, text_size, result, full_key2);
		std::string hash = CryptoLib::MD5(result, text_size);
		if (pairs.find(hash) != pairs.end())
		{
			(*result_key1) = pairs[hash];
			(*result_key2) = full_key2;
			return true;
		}
	}
	return false;
}

