CC=gcc

CFLAGS=-I.
INCLUDES = bitcpy.h

%.o: %.c $(INCLUDES)
	$(CC) -c -o $@ $< $(CFLAGS)

mainmake: main.o
	$(CC) -o trybitcpy main.o
