#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <bzlib.h>

#include "file_helper.h"
#include "chunks.h"

int main()
{
	printf("%d\n", sizeof(struct ChunkGEN8));
	bool be = false;
	FILE *iff = fopen("deltarune.win", "rb");
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
		if(buffer == ID_TXTR)
		{
			ereadUint32(iff, be);
			break;
		}
		buffer = ereadUint32(iff, be);
		printf("%d\n", buffer);
		fseek(iff, buffer, SEEK_CUR);
	}
	uint32_t textureCount = ereadUint32(iff, be);
	printf("texcount: %d\n", textureCount);

	uint32_t* texturePointers = (uint32_t*)malloc(textureCount * sizeof(uint32_t));
	if(texturePointers == NULL)
	{
		printf("error on allocating texturePointers, aborting...\n");
		return 1;
	}

	for(int i=0; i<textureCount; i++)
	{
		texturePointers[i] = ereadUint32(iff, be);
		printf("texpointers %d\n", texturePointers[i]);
	}

	fseek(iff, texturePointers[1], SEEK_SET);
	ereadUint32(iff, be);
	ereadUint32(iff, be);
	ereadUint32(iff, be);
	fseek(iff, ereadUint32(iff, be), SEEK_SET);
	if(ereadUint32(iff, be) != TEXTURE_HEADER_QOZ2)
	{
		printf("expected qoz2 in image file!\n");
		return 1;
	}
	printf("%d\t%d\n", ereadUint16(iff, be), ereadUint16(iff, be));
	int qoz2_decompressed_length = ereadUint32(iff, be);

	int bz_error = 5;
	BZFILE* qoz2 = BZ2_bzReadOpen(&bz_error, iff, 4, false, NULL, 0);
	if(bz_error != BZ_OK)
	{
		printf("error opening bz2 image! bz2lib gave code %d\n", bz_error);
		return 1;
	}

	FILE* outqoi = fopen("out.gmqoi", "wb");
	if(outqoi == NULL)
	{
		printf("failed to create out GMQOI file!\n");
		return 1;
	}

	uint8_t bzqoi_buffer;
	for(int i=0;i<qoz2_decompressed_length;i++)
	{
		BZ2_bzRead(&bz_error, qoz2, &bzqoi_buffer, sizeof(bzqoi_buffer));
		fputc(bzqoi_buffer, outqoi);
	}
	/*
	// code for ROOM
	uint32_t roomCount = ereadUint32(iff, be);
	printf("%d\n", roomCount);

	uint32_t* roomPointers = (uint32_t*)malloc(roomCount * sizeof(uint32_t));
	if(roomPointers == NULL)
	{
		printf("failed initializing pointers array!\n");
		return 1;
	}

	for(int i=0;i<roomCount;i++)
	{
		roomPointers[i] = ereadUint32(iff, be);
		printf("%d\n", roomPointers[i]);
	}

	free(roomPointers);
	*/
	return 0;
}
