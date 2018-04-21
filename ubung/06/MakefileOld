CC=gcc
CFLAGS=-Wall -pthread -std=c99
DEBUG=-O0 -g
OBJFLAG=-c
AS=as

all: deadlock

deadlock: deadlock.c deadlock.h
	$(CC) $(CFLAGS) $(DEBUG) -fPIC deadlock.c -o deadlock

clean:
	rm -vfr *~ *.o deadlock
