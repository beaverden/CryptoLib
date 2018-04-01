#include "stdafx.h"
#include "RSA.h"
#include <sstream>


std::string CryptoLib::RSA::ZZToB64(const NTL::ZZ& num) {
	size_t output_length = NTL::NumBytes(num);
	uint8_t* output = new uint8_t[output_length];
	NTL::BytesFromZZ(output, num, output_length);
	std::string result;
	CryptoLib::Base64::Base64Encode(
		output,
		output_length,
		result
	);
	return result;
}

NTL::ZZ CryptoLib::RSA::B64ToZZ(const std::string& input) {
	size_t decoded_len = 0;
	void* decoded = CryptoLib::Base64::Base64Decode(
		(void*)input.c_str(),
		input.length(),
		&decoded_len
	);
	NTL::ZZ res = NTL::ZZFromBytes((uint8_t*)decoded, decoded_len);
	return res;
}

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



void CryptoLib::RSA::ExportPublicKey(RSA_CONTEXT* ctx, char* file_path) {
	std::string exp_enc = ZZToB64(ctx->publicExponent);
	std::string mod_enc = ZZToB64(ctx->publicModulus);

	std::ofstream f(file_path, std::ios::binary);
	f << "-----BEGIN RSA PRIVATE KEY-----\n"
		<< exp_enc << std::endl << mod_enc << std::endl
		<< "-----END RSA PRIVATE KEY-----";
	f.close();
}

void CryptoLib::RSA::ExportPrivateKey(RSA_CONTEXT* ctx, char* file_path) {
	std::string prv_enc = ZZToB64(ctx->privateExponent);
	std::string mod_enc = ZZToB64(ctx->publicModulus);

	std::ofstream f(file_path, std::ios::binary);
	f	<< "-----BEGIN RSA PRIVATE KEY-----\n"
		<< prv_enc << std::endl << mod_enc << std::endl
		<< "-----END RSA PRIVATE KEY-----";
	f.close();
}


void CryptoLib::RSA::ImportPublicKey(RSA_CONTEXT* ctx, char* file_path) {
	std::ifstream f(file_path, std::ios::binary);
	std::string exp_enc;
	std::string mod_enc;
	std::string temp;
	std::getline(f, temp);
	std::getline(f, exp_enc);
	std::getline(f, mod_enc);
	f.close();
	ctx->publicExponent = B64ToZZ(exp_enc);
	ctx->publicModulus = B64ToZZ(mod_enc);
}

void CryptoLib::RSA::ImportPrivateKey(RSA_CONTEXT* ctx, char* file_path) {
	std::ifstream f(file_path, std::ios::binary);
	std::string prv_enc;
	std::string mod_enc;
	std::string temp;
	std::getline(f, temp);
	std::getline(f, prv_enc);
	std::getline(f, mod_enc);
	f.close();
	ctx->privateExponent = B64ToZZ(prv_enc);
	ctx->publicModulus = B64ToZZ(mod_enc);
}