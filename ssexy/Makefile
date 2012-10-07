CC = gcc
CFLAGS = -Wall -m32

# strip binary
CFLAGS += -s -static -nostdlib -e Main

chal.out: chal.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm chal.out
