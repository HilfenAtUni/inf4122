CC=gcc
CFLAGS=-Wall -pthread -std=c99
DEBUG=-O0 -g
OBJFLAG=-c
AS=as

all: mmu secondchance aging lru

mmu:
	$(CC) $(CFLAGS) $(DEBUG) -fPIC mmu.c -o mmu

lru:
	$(CC) $(CFLAGS) $(DEBUG) -fPIC lru.c -o lru

aging:
	$(CC) $(CFLAGS) $(DEBUG) -fPIC aging.c -o aging

secondchance:
	$(CC) $(CFLAGS) $(DEBUG) -fPIC secondchance.c -o secondchance

clean:
	rm -vfr *~ *.o mmu secondchance aging lru