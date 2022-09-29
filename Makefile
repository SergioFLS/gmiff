CC=clang
FLAGS=--std=c99 -Wall -g

SRCDIR=src
OBJDIR=obj

BZ2_DIR=third-party/bzip2
BZ2_OBJ=$(OBJDIR)/bzip2
BZ2_FILES=$(BZ2_DIR)/blocksort.c \
	  $(BZ2_DIR)/huffman.c \
	  $(BZ2_DIR)/crctable.c \
	  $(BZ2_DIR)/randtable.c \
	  $(BZ2_DIR)/compress.c \
	  $(BZ2_DIR)/decompress.c \
	  $(BZ2_DIR)/bzlib.c
_BZ2_O=$(BZ2_FILES:$(BZ2_DIR)/%=$(BZ2_OBJ)/%)
BZ2_O=$(_BZ2_O:.c=.o)

SRC_FILES=$(SRCDIR)/chunks.c \
	  $(SRCDIR)/file_helper.c \
	  $(SRCDIR)/gmiff.c
_SRC_O=$(SRC_FILES:$(SRCDIR)/%=$(OBJDIR)/%)
SRC_O=$(_SRC_O:.c=.o)

OUT=gmiff

all: $(OUT)

$(OUT): $(BZ2_O) $(SRC_O)
	$(CC) $(FLAGS) -I$(BZ2_DIR) -o $@ $?

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(FLAGS) -c -o $@ $<

$(BZ2_OBJ)/%.o: $(BZ2_DIR)/%.c
	$(CC) $(FLAGS) -c -o $@ $<

#bzip2: $(BZ2_O)
#build: $(BZ2_O) $(GMIFF_O)
#	$(CC) $(FLAGS) -I$(BZ2_LIB) -o $(OUT) $(BZ2_O) $(GMIFF_O)
#
#$(GMIFF_O): chunks.c file_helper.c gmiff.c
#	$(CC) $(FLAGS) -c chunks.c file_helper.c gmiff.c
