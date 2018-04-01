#pragma once
#include <string>
#include <memory>
#include "CryptoLib.h"

namespace CryptoLib {
	namespace Base64 {
		CRYPTO_API bool Base64Encode(
			void* input_buffer,
			size_t input_length,
			std::string& output,
			char* alphabet = nullptr,
			size_t alphabet_length = 64,
			char padding = '='
		);
		CRYPTO_API void* Base64Decode(
			void* input_buffer,
			size_t input_length,
			size_t* output_length,
			char* alphabet = nullptr,
			size_t alphabet_length = 64,
			char padding = '='
		);
	};
};