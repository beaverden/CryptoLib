#pragma once
#include "NTL/ZZ.h"
#include <sstream>

namespace CryptoLib {
	namespace RSA {
		struct RSA_CONTEXT 
		{
			NTL::ZZ publicExponent;
			NTL::ZZ privateExponent;
			NTL::ZZ publicModulus;
		};

		__declspec(dllexport) void RSAKeyGen(RSA_CONTEXT* ctx);
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
