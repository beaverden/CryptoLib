#pragma once
#include "NTL/ZZ.h"
#include "Base64.h"
#include <fstream>
#include <sstream>


namespace CryptoLib {
	namespace RSA {
		struct RSA_CONTEXT 
		{
			NTL::ZZ publicExponent;
			NTL::ZZ privateExponent;
			NTL::ZZ publicModulus;
		};
		
		std::string ZZToB64(const NTL::ZZ& num);
		NTL::ZZ B64ToZZ(const std::string& input);

		__declspec(dllexport) void RSAKeyGen(RSA_CONTEXT* ctx);
		__declspec(dllexport) void ImportPublicKey(RSA_CONTEXT* ctx, char* file_path);
		__declspec(dllexport) void ImportPrivateKey(RSA_CONTEXT* ctx, char* file_path);
		__declspec(dllexport) void ExportPublicKey(RSA_CONTEXT* ctx, char* file_path);
		__declspec(dllexport) void ExportPrivateKey(RSA_CONTEXT* ctx, char* file_path);

		__declspec(dllexport) void RSAEncrypt(
			void* plaintext, 
			size_t plaintext_length,
			void* ciphertext,
			size_t* ciphertext_length,
			RSA_CONTEXT* ctx
		);
		__declspec(dllexport) void RSADecrypt(
			void* ciphertext,
			size_t ciphertext_length,
			void* plaintext,
			size_t* plaintext_length,
			RSA_CONTEXT* ctx
		);

	};
};
