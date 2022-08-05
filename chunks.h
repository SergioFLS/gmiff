#ifndef CHUNKS_H
#define CHUNKS_H

#define ID_FORM 0x4d524f46
#define ID_GEN8 0x384e4547
#define ID_OPTN 0x4e54504f
#define ID_ROOM 0x4d4f4f52
#define ID_TXTR 0x52545854

// texture-specific
#define TEXTURE_HEADER_QOZ2 0x716f7a32 /* bzip2-compressed GMQOI */
#define TEXTURE_HEADER_QOIF 0x716f6966 /* uncompressed GMQOI */

// https://github.com/colinator27/DogScepter/blob/master/DogScepterLib/Core/Chunks/GMChunkGEN8.cs
// https://github.com/krzys-h/UndertaleModTool/blob/master/UndertaleModLib/Models/UndertaleGeneralInfo.cs
// thanks for documenting the format <3

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

struct ChunkROOM
{
	uint32_t namePointer;
	uint32_t captionPointer;
	uint32_t width;
	uint32_t height;
	uint32_t speed;
	uint8_t persistent;
	uint32_t backgroundColor;
	uint8_t showBackgroundColor;
	uint32_t creationCodeID;
	uint32_t flags;
	uint32_t backgroundsPointer;
	// TODO complete ROOM chunk
};

void readChunkGEN8(struct ChunkGEN8* chunkGEN8, FILE* data, bool be);
#endif
