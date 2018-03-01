CC=gcc
CFLAGS=-Wall -std=c99
DEBUG=-O0 -g

all: mydir statistics

mydir:
	$(CC) $(CFLAGS) $(DEBUG) mydir.c -o mydir

statistics:
	$(CC) $(CFLAGS) $(DEBUG) statistics.c -o statistics

clean:
	rm -vfr *~ mydir statistics
