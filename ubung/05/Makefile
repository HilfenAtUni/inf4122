CC=gcc
CFLAGS=-Wall -pthread -std=c99
DEBUG=-O0 -g

all: mutex.o test_mutex test.s my_tsl.o my_mutex.o test_my_mutex

mutex.o:
	$(CC) $(CFLAGS) $(DEBUG) mutex.c -o mutex.o

test_mutex: mutex.o
	$(CC) $(CFLAGS) $(DEBUG) tsl.o mutex.o test_mutex.c -o test_mutex

test.s:
	$(CC) -O2 -S test.c -o test.s

my_tsl.o:
	$(CC) $(CFLAGS) $(DEBUG) my_tsl.s -o my_tsl.o

my_mutex.o:
	$(CC) $(CFLAGS) $(DEBUG) my_mutex.c -o my_mutex.o

test_my_mutex: my_mutex.o
	$(CC) $(CFLAGS) $(DEBUG) my_mutex.o test_my_mutex.c -o test_my_mutex

clean:
	rm -vfr *~ *.s mutex.o my_mutex.o test_mutex test_my_mutex
