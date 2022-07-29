CC=clang
FLAGS=--std=c99 -Wall
IN=file_helper.c gmiff.c
OUT=gmiff

build:
	$(CC) $(FLAGS) -o $(OUT) $(IN)
