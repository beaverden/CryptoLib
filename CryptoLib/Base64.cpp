#include "stdafx.h"
#include "Base64.h"

bool CryptoLib::Base64::Base64Encode(
	void* input_buffer,
	size_t input_length,
	std::string& output,
	char* alphabet,
	size_t alphabet_length,
	char padding
)
{
	output = "";
	if (alphabet == nullptr) {
		alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	}
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
		if (value >= alphabet_length) {
			return false;
		}
		output += (char)alphabet[value];
	}
	while (output.length() % 4 != 0)
	{
		output += padding;
	}
	return true;
}

void* CryptoLib::Base64::Base64Decode(
	void* input_buffer,
	size_t input_length,
	size_t* output_length,
	char* alphabet,
	size_t alphabet_length,
	char padding
)
{
	if ((input_length & 0x3) != 0) {
		return nullptr;
	}
	if (alphabet == nullptr) {
		alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	}
	uint8_t assoc[256] = { 0 };
	memset(assoc, 0xFF, 256);
	for (size_t i = 0; i < alphabet_length; i++) {
		assoc[alphabet[i]] = i;
	}

	(*output_length) = (input_length * 3) / 4;
	uint8_t* in_buff = (uint8_t*)(input_buffer);
	uint8_t* out_buff = new uint8_t[(*output_length)+1];
	memset(out_buff, 0, (*output_length)+1);

	
	int group_type = 0;
	int out_index = 0;
	for (size_t i = 0; i < input_length; i++) {
		if (assoc[in_buff[i]] == 0xFF && in_buff[i] != padding) {
			delete[] out_buff;
			return nullptr;
		}
		uint8_t value = assoc[in_buff[i]];
		if (in_buff[i] == '=') break;
		switch (group_type) {
		case 0:
			out_buff[out_index] |= (value << 2);
			break;
		case 1:
			out_buff[out_index] |= ((value & 0x30) >> 4);
			out_buff[out_index + 1] |= ((value & 0xF) << 4);
			out_index++;
			break;
		case 2:
			out_buff[out_index] |= ((value & 0x3C) >> 2);
			out_buff[out_index + 1] |= ((value & 0x3) << 6);
			out_index++;
			break;
		case 3:
			out_buff[out_index] |= value;
			out_index++;
			break;
		}
		group_type = (group_type + 1) % 4;
	}
	return out_buff;
}