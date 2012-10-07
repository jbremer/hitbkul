CC = gcc
CFLAGS = -std=c99 -Wall -m32

# completely strip the binary
CFLAGS += -s -static -nostdlib -e Main -lc

default: obf

obf: obf.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm obf
