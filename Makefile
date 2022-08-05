CC=clang
FLAGS=--std=c99 -Wall

BZ2_LIB=third-party/bzip2
BZ2_O=blocksort.o huffman.o crctable.o randtable.o compress.o decompress.o bzlib.o

GMIFF_O=chunks.o file_helper.o gmiff.o
OUT=gmiff

all: build

build: $(BZ2_O) $(GMIFF_O)
	$(CC) $(FLAGS) -o $(OUT) $(BZ2_O) $(GMIFF_O)

$(GMIFF_O): chunks.c file_helper.c gmiff.c
	$(CC) $(FLAGS) -c chunks.c file_helper.c gmiff.c

$(BZ2_O):
	$(CC) $(FLAGS) -c $(BZ2_LIB)/blocksort.c $(BZ2_LIB)/huffman.c $(BZ2_LIB)/crctable.c $(BZ2_LIB)/randtable.c $(BZ2_LIB)/compress.c $(BZ2_LIB)/decompress.c $(BZ2_LIB)/bzlib.c
