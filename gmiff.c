#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "file_helper.h"
#include "chunks.h"


// https://codereview.stackexchange.com/a/151070
/*
static inline uint32_t reverseBytes(uint32_t value)
{
	return (value & 0xFF000000) >> 24 |
		(value & 0x00FF0000) >> 8 |
		(value & 0x0000FF00) << 8 |
		(value & 0x000000FF) << 24;
}

static inline uint16_t reverseBytes16(uint16_t value)
{
	return (value & 0xFF00) >> 8 |
		(value & 0x00FF) << 8;
}

uint32_t efread(FILE *f, bool be)
{
	uint32_t output;
	fread(&output, sizeof(uint32_t), 1, f);
	if(be)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
		return reverseBytes(output);
	return output;
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
		return output;
	return reverseBytes(output);
#else
#error unsupported endianness
#endif
}

uint16_t efread16(FILE *f, bool be)
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
*/

// https://github.com/colinator27/DogScepter/blob/master/DogScepterLib/Core/Chunks/GMChunkGEN8.cs
// https://github.com/krzys-h/UndertaleModTool/blob/master/UndertaleModLib/Models/UndertaleGeneralInfo.cs

int main()
{
	printf("%d\n", sizeof(struct ChunkGEN8));
	bool be = false;
	FILE *iff = fopen("pool.win", "rb");
	if(iff == NULL)
	{
		printf("failed to read file!");
		return 1;
	}

	//printf("%d\n", reverseBytes32(ID_FORM));
	uint32_t buffer;
	uint32_t fileSize;
	buffer = ereadUint32(iff, false);
	if(buffer != ID_FORM)
	{
		if(reverseBytes32(buffer) == ID_FORM)
		{
			printf("Data file is in big endian\n");
			be = true;
		}
		else
		{
			printf("magic didn't match FORM! (might be a completely different file?)\n");
			return 1;
		}
	}

	fileSize = ereadUint32(iff, be);
	printf("size of FORM is %d bytes long\n", fileSize);

	while(ftell(iff) < fileSize + 8)
	{
		buffer = ereadUint32(iff, be);
		printf("%c%c%c%c (0x%08X)\n",
				(char)(buffer & 0x000000FF),
				(char)((buffer & 0x0000FF00) >> 8),
				(char)((buffer & 0x00FF0000) >> 16),
				(char)((buffer & 0xFF000000) >> 24),
				buffer);

		if(buffer == ID_GEN8)
		{
			ereadUint32(iff, be);
			break;
		}
		buffer = ereadUint32(iff, be);
		printf("%d\n", buffer);
		fseek(iff, buffer, SEEK_CUR);
	}
	struct ChunkGEN8 chunkGenInfo;
	fread(&chunkGenInfo.disableDebug, sizeof(uint8_t), 1, iff);
	fread(&chunkGenInfo.formatID, sizeof(uint8_t), 1, iff);
	chunkGenInfo.unknown = ereadUint16(iff, be);
	chunkGenInfo.filenamePointer = ereadUint32(iff, be);
	chunkGenInfo.configPointer = ereadUint32(iff, be);
	chunkGenInfo.lastObjectID = ereadUint32(iff, be);
	chunkGenInfo.lastTileID = ereadUint32(iff, be);
	chunkGenInfo.gameID = ereadUint32(iff, be);
	fread(&chunkGenInfo.guid, sizeof(uint8_t), 16, iff);
	chunkGenInfo.namePointer = ereadUint32(iff, be);
	chunkGenInfo.major = ereadUint32(iff, be);
	chunkGenInfo.minor = ereadUint32(iff, be);
	chunkGenInfo.release = ereadUint32(iff, be);
	chunkGenInfo.build = ereadUint32(iff, be);

	printf("%d.%d.%d.%d\n", chunkGenInfo.major, chunkGenInfo.minor, chunkGenInfo.release, chunkGenInfo.build);
	return 0;
}
