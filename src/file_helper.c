#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "file_helper.h"

// https://codereview.stackexchange.com/a/151070

extern inline uint64_t reverseBytes64(uint64_t value)
{
	return (value & 0xFF00000000000000) >> 56 |
		(value & 0x00FF000000000000) >> 40 |
		(value & 0x0000FF0000000000) >> 16 |
		(value & 0x000000FF00000000) >> 8 |
		(value & 0x00000000FF000000) << 8 |
		(value & 0x0000000000FF0000) << 16 |
		(value & 0x000000000000FF00) << 40 |
		(value & 0x00000000000000FF) << 56;
}

extern inline uint32_t reverseBytes32(uint32_t value)
{
	return (value & 0xFF000000) >> 24 |
		(value & 0x00FF0000) >> 8 |
		(value & 0x0000FF00) << 8 |
		(value & 0x000000FF) << 24;
}

extern inline uint16_t reverseBytes16(uint16_t value)
{
	return (value & 0xFF00) >> 8 |
		(value & 0x00FF) << 8;
}

uint64_t ereadUint64(FILE *f, bool be)
{
	uint64_t output;
	fread(&output, sizeof(uint64_t), 1, f);
	if(be)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return reverseBytes64(output);
	return output;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		return output;
	return reverseBytes64(output);
#else
#error unsupported endianness
#endif
}

uint32_t ereadUint32(FILE *f, bool be)
{
	uint32_t output;
	fread(&output, sizeof(uint32_t), 1, f);
	if(be)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return reverseBytes32(output);
	return output;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		return output;
	return reverseBytes32(output);
#else
#error unsupported endianness
#endif
}

uint16_t ereadUint16(FILE *f, bool be)
{
	uint16_t output;
	fread(&output, sizeof(uint16_t), 1, f);
	if(be)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return reverseBytes16(output);
	return output;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		return output;
	return reverseBytes16(output);
#else
#error unsupported endianness
#endif
}
