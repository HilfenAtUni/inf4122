CC=gcc
CFLAGS=-Wall -pthread -std=c99
DEBUG=-O0 -g
OBJFLAG=-c
AS=as

all: mutex.o test_mutex test.s my_tsl.o my_mutex.o test_my_mutex

mutex.o: mutex.c mutex.h
	$(CC) $(CFLAGS) $(DEBUG) -fPIC $(OBJFLAG) mutex.c -o mutex.o

test_mutex: mutex.o test_mutex.c
	$(CC) $(CFLAGS) $(DEBUG) tsl.o mutex.o test_mutex.c -o test_mutex

test.s:
	$(CC) -O2 -S test.c -o test.s

my_tsl.o:
	$(AS) my_tsl.s -o my_tsl.o

my_mutex.o: my_mutex.c my_mutex.h
	$(CC) $(CFLAGS) $(DEBUG) $(OBJFLAG) my_mutex.c -o my_mutex.o

test_my_mutex: my_tsl.o my_mutex.o test_my_mutex.c
	$(CC) $(CFLAGS) $(DEBUG) my_tsl.o my_mutex.o test_my_mutex.c -o test_my_mutex

clean:
	rm -vfr *~ mutex.o my_mutex.o test_mutex test.s my_tsl.o test_my_mutex
