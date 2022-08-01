#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "file_helper.h"
#include "chunks.h"

int main()
{
	printf("%d\n", sizeof(struct ChunkGEN8));
	bool be = false;
	FILE *iff = fopen("pool.win", "rb");
	if(iff == NULL)
	{
		printf("failed to read file!\n");
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
	readChunkGEN8(&chunkGenInfo, iff, be);

	printf("%llX\n", chunkGenInfo.timestamp);
	return 0;
}
