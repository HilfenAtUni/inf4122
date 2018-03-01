CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g

all: mycopy reverse

mycopy:
	$(CC) $(CFLAGS) $(DEBUG) mycopy.c -o mycopy

reverse:
	$(CC) $(CFLAGS) $(DEBUG) reverse.c -o reverse

clean:
	rm -vfr *~ mycopy reverse
