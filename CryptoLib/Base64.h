#pragma once
#include <string>


namespace CryptoLib {
	namespace Base64 {
		__declspec(dllexport) std::string Base64Enconde(
			void* input_buffer,
			size_t input_length,
			char* alphabet = nullptr,
			char padding = '='
		);
		__declspec(dllexport) void Base64Decode(
			void* input_buffer,
			size_t input_length,
			void* output_buffer,
			size_t* output_length,
			char* alphabet = nullptr,
			size_t alphabet_length = 64,
			char padding = '='
		);
	};
};