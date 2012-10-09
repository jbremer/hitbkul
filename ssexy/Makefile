CC = gcc
CFLAGS = -Wall -m32
LIBS = -lpthread

# strip binary
CFLAGS += -s -nostdlib -e Main -pie

chal.out: chal.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

chal.ssexy: chal.out
	python ssexy.py $@ 0x54e > chal.s
	gcc -e Main -nostdlib -m32 -lc chal.s -o $^

clean:
	rm chal.out chal.ssexy
