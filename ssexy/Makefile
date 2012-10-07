CC = gcc
CFLAGS = -Wall -m32
LIBS = -lpthread

# strip binary
CFLAGS += -s -nostdlib -e Main

chal.out: chal.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm chal.out
