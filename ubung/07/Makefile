CC=gcc
CFLAGS=-Wall -pthread
DEBUG=-O0 -g

all: sender

sender:
	$(CC) $(CFLAGS) $(DEBUG) sender.c -o sender

clean:
	rm -vfr *~ *.o sender
