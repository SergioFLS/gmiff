#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "file_helper.h"

#include "chunks.h"

void readChunkGEN8(struct ChunkGEN8* chunkGEN8, FILE* data, bool be)
{
	fread(&chunkGEN8->disableDebug, sizeof(uint8_t), 1, data);
	fread(&chunkGEN8->formatID, sizeof(uint8_t), 1, data);
	chunkGEN8->unknown = ereadUint16(data, be);
	chunkGEN8->filenamePointer = ereadUint32(data, be);
	chunkGEN8->configPointer = ereadUint32(data, be);
	chunkGEN8->lastObjectID = ereadUint32(data, be);
	chunkGEN8->lastTileID = ereadUint32(data, be);
	chunkGEN8->gameID = ereadUint32(data, be);
	fread(&chunkGEN8->guid, sizeof(uint8_t), 16, data);
	chunkGEN8->namePointer = ereadUint32(data, be);
	chunkGEN8->major = ereadUint32(data, be);
	chunkGEN8->minor = ereadUint32(data, be);
	chunkGEN8->release = ereadUint32(data, be);
	chunkGEN8->build = ereadUint32(data, be);
	chunkGEN8->defaultWindowWidth = ereadUint32(data, be);
	chunkGEN8->defaultWindowHeight = ereadUint32(data, be);
	chunkGEN8->infoFlags = ereadUint32(data, be);
	chunkGEN8->licenseCRC32 = ereadUint32(data, be);
	fread(&chunkGEN8->licenseMD5, sizeof(uint8_t), 16, data);
	chunkGEN8->timestamp = ereadUint64(data, be);
	chunkGEN8->displayNamePointer = ereadUint32(data, be);
	chunkGEN8->activeTargets = ereadUint64(data, be);
	chunkGEN8->steamAppID = ereadUint32(data, be);
}

