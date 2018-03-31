#include "stdafx.h"
#include "Base64.h"

std::string CryptoLib::Base64::Base64Enconde(
	void* input_buffer,
	size_t input_length
)
{
	std::string result = "";
	const char* BASE64_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	uint8_t* buff = (uint8_t*)input_buffer;
	int group_type = 0;
	size_t index = 0;
	while (index < input_length) 
	{
		uint8_t value = 0;
		switch (group_type) 
		{
		case 0: 
			value = (buff[index] & 0xFC) >> 2;
			break;
		case 1:
			value = ((buff[index] & 0x3) << 4);
			if (index + 1 < input_length) {
				value |= ((buff[index + 1] & 0xF0) >> 4);
			}
			index++;
			break;
		case 2:
			value = ((buff[index] & 0xF) << 2);
			if (index + 1 < input_length) {
				value |= ((buff[index + 1] & 0xC0) >> 6);
			}
			index++;
			break;
		case 3:
			value = (buff[index] & 0x3F);
			index++;
			break;
		}
		group_type = (group_type + 1) % 4;
		result += (char)BASE64_ALPHABET[value];
	}
	while (result.length() % 4 != 0) 
	{
		result += "=";
	}
	return result;
}