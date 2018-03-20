#pragma once

#define IS_BIG_ENDIAN (*(uint16_t *)"\x00\xff" < 0x100)
#define LEFT_ROTATE(n, i) (((n) << (i)) | ((n) >> (32 - (i))))
#define RIGHT_ROTATE(n, i) (((n) >> (i)) | ((n) << (32 - (i))))
#define BYTE_SIZE 8
#define SIZE_INT_64 64
#define NEAREST_512_MULTIPLE(n) ((((n) + 512 - 1) >> 9) << 9)
#define REVERSE_64(n)\
		((((n) & 0xFF00000000000000ULL) >> 56) |\
		 (((n) & 0x00FF000000000000ULL) >> 40) |\
		 (((n) & 0x0000FF0000000000ULL) >> 24) |\
		 (((n) & 0x000000FF00000000ULL) >> 8)  |\
		 (((n) & 0x00000000000000FFULL) << 56) |\
		 (((n) & 0x000000000000FF00ULL) << 40) |\
		 (((n) & 0x0000000000FF0000ULL) << 24) |\
		 (((n) & 0x00000000FF000000ULL) << 8))
#define REVERSE_32(n)\
		((((n) & 0xFF000000) >> 24) |\
		 (((n) & 0x00FF0000) >> 8)  |\
		 (((n) & 0x0000FF00) << 8)  |\
		 (((n) & 0x000000FF) << 24))