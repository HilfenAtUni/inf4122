CC=gcc
CFLAGS=-Wall -pthread -std=c99
DEBUG=-O0 -g

all:
	$(CC) $(CFLAGS) $(DEBUG) hellothread.c -o hellothread
	$(CC) $(CFLAGS) $(DEBUG) square.c -o square

hellothread:
	$(CC) $(CFLAGS) $(DEBUG) hellothread.c -o hellothread

square:
	$(CC) $(CFLAGS) $(DEBUG) square.c -o square


clean:
	rm -vfr *~ hellothread square
