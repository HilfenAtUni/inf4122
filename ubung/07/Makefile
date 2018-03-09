CC=gcc
CFLAGS=-Wall -pthread
DEBUG=-O0 -g

all: sender

logger.o:
	$(CC) $(CFLAGS) $(DEBUG) -c logger.c -o logger.o

sender: logger.o
	$(CC) $(CFLAGS) $(DEBUG) logger.o sender.c -o sender

receiver:
	$(CC) $(CFLAGS) $(DEBUG) receiver.c -o receiver

clean:
	rm -vfr *~ *.o sender receiver
