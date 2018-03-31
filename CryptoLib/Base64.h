#pragma once
#include <string>


namespace CryptoLib {
	namespace Base64 {
		__declspec(dllexport) std::string Base64Enconde(
			void* input_buffer,
			size_t input_length
		);
	};
};