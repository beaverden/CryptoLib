#include "stdafx.h"
#include "RSA.h"
#include <sstream>

void CryptoLib::RSA::RSAKeyGen(CryptoLib::RSA::RSA_CONTEXT* ctx) 
{
	NTL::ZZ prime1;
	NTL::ZZ prime2;
	NTL::ZZ prime_product;
	NTL::ZZ euler_totient;

	GenPrime(prime1, 1024);
	GenPrime(prime2, 1024);
	prime_product = prime1 * prime2;
	euler_totient = (prime1 - 1) * (prime2 - 1);
	NTL::ZZ e(65537);
	NTL::ZZ d = NTL::InvMod(e, euler_totient);

	ctx->publicModulus = prime_product;
	ctx->publicExponent = e;
	ctx->privateExponent = d;
}

void CryptoLib::RSA::RSAEncrypt(
	void* plaintext, 
	size_t plaintext_length,
	void* ciphertext,
	size_t* ciphertext_length,
	RSA_CONTEXT* ctx
) 
{
	NTL::ZZ message_integer = NTL::ZZFromBytes((uint8_t*)plaintext, plaintext_length);
	NTL::ZZ ciphertext_integer = NTL::PowerMod(
		message_integer,
		ctx->publicExponent,
		ctx->publicModulus
	);
	NTL::BytesFromZZ((unsigned char*)ciphertext, ciphertext_integer, NTL::NumBytes(ciphertext_integer));
	(*ciphertext_length) = NTL::NumBytes(ciphertext_integer);
}

void CryptoLib::RSA::RSADecrypt(
	void* ciphertext,
	size_t ciphertext_length,
	void* plaintext,
	size_t* plaintext_length,
	RSA_CONTEXT* ctx
)
{
	NTL::ZZ message_integer = NTL::ZZFromBytes((uint8_t*)ciphertext, ciphertext_length);
	NTL::ZZ plaintext_integer = NTL::PowerMod(
		message_integer,
		ctx->privateExponent,
		ctx->publicModulus
	);
	NTL::BytesFromZZ((unsigned char*)plaintext, plaintext_integer, NTL::NumBytes(plaintext_integer));
	(*plaintext_length) = NTL::NumBytes(plaintext_integer);
}
