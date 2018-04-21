CC=gcc
CFLAGS=-Wall -pthread -std=c99
DEBUG=-O0 -g

all: hellothread square square2

hellothread:
	$(CC) $(CFLAGS) $(DEBUG) hellothread.c -o hellothread

square:
	$(CC) $(CFLAGS) $(DEBUG) square.c -o square

square2:
	$(CC) $(CFLAGS) $(DEBUG) square2.c -o square2

clean:
	rm -vfr *~ *.o hellothread square square2
