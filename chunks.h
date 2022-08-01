#ifndef CHUNKS_H
#define CHUNKS_H

#define ID_FORM 0x4d524f46
#define ID_GEN8 0x384e4547
#define ID_OPTN 0x4e54504f


// https://github.com/colinator27/DogScepter/blob/master/DogScepterLib/Core/Chunks/GMChunkGEN8.cs
// // https://github.com/krzys-h/UndertaleModTool/blob/master/UndertaleModLib/Models/UndertaleGeneralInfo.cs

struct ChunkGEN8
{
	uint8_t disableDebug;
	uint8_t formatID;
	uint16_t unknown;
	uint32_t filenamePointer;
	uint32_t configPointer;
	uint32_t lastObjectID;
	uint32_t lastTileID;
	uint32_t gameID;
	uint8_t guid[16];
	uint32_t namePointer;
	uint32_t major;
	uint32_t minor;
	uint32_t release;
	uint32_t build;
	uint32_t defaultWindowWidth;
	uint32_t defaultWindowHeight;
	uint32_t infoFlags;
	uint32_t licenseCRC32;
	uint8_t licenseMD5[16];
	int64_t timestamp;
	uint32_t displayNamePointer;
	int64_t activeTargets;
	uint64_t functionClassifications;
	uint32_t steamAppID;
};

void readChunkGEN8(struct ChunkGEN8* chunkGEN8, FILE* data, bool be);
#endif
