#pragma once
#include <string>
#include <memory>

namespace CryptoLib {
	namespace Base64 {
		__declspec(dllexport) bool Base64Encode(
			void* input_buffer,
			size_t input_length,
			std::string& output,
			char* alphabet = nullptr,
			size_t alphabet_length = 64,
			char padding = '='
		);
		__declspec(dllexport) void* Base64Decode(
			void* input_buffer,
			size_t input_length,
			size_t* output_length,
			char* alphabet = nullptr,
			size_t alphabet_length = 64,
			char padding = '='
		);
	};
};