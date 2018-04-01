#pragma once
#include "NTL/ZZ.h"
#include "Base64.h"
#include <fstream>
#include <sstream>
#include "CryptoLib.h"
#include <vector>

namespace CryptoLib {
	namespace RSA {
		enum RSA_DECRYPTION_TYPE {
			DECRYPTION_PRIVATE_KEY,
			DECRYPTION_CRT
		};

		struct RSA_CONTEXT 
		{
			NTL::ZZ publicExponent;
			NTL::ZZ privateExponent;
			NTL::ZZ publicModulus;

			NTL::ZZ privateP;
			NTL::ZZ privateQ;
			RSA_DECRYPTION_TYPE decryptionType = DECRYPTION_PRIVATE_KEY;
		};
		
		std::string ZZToB64(const NTL::ZZ& num);
		NTL::ZZ B64ToZZ(const std::string& input);
		CRYPTO_API std::vector<NTL::ZZ> ContinuedFraction(const NTL::ZZ& a, const NTL::ZZ& b);
		CRYPTO_API std::vector<std::pair<NTL::ZZ, NTL::ZZ>> Convergents(const std::vector<NTL::ZZ>& continued);
		
		CRYPTO_API void RSAKeyGenWeak(RSA_CONTEXT* ctx);
		CRYPTO_API void RSAKeyGen(RSA_CONTEXT* ctx);
		CRYPTO_API void ImportPublicKey(RSA_CONTEXT* ctx, char* file_path);
		CRYPTO_API void ImportPrivateKey(RSA_CONTEXT* ctx, char* file_path);
		CRYPTO_API void ExportPublicKey(RSA_CONTEXT* ctx, char* file_path);
		CRYPTO_API void ExportPrivateKey(RSA_CONTEXT* ctx, char* file_path);

		CRYPTO_API void RSAEncrypt(
			void* plaintext, 
			size_t plaintext_length,
			void* ciphertext,
			size_t* ciphertext_length,
			RSA_CONTEXT* ctx
		);
		CRYPTO_API void RSADecrypt(
			void* ciphertext,
			size_t ciphertext_length,
			void* plaintext,
			size_t* plaintext_length,
			RSA_CONTEXT* ctx
		);

		CRYPTO_API bool WiennerAttack(
			RSA_CONTEXT* ctx
		);

	};
};
