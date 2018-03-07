#ifndef __DEADLOCK_H__
#define __DEADLOCK_H__
#include <pthread.h>

typedef struct respool_ {
	unsigned char lock;
	int A;
	int B;
	int C;
	// int mask;
} respool_t;

typedef struct respool_ * respool_p;

typedef struct threadinfo_ {
	pthread_t thread;
	respool_p pool;
	int A;
	int B;
	int C;
} threadinfo_t;

typedef struct threadinfo_ * threadinfo_p;

void * Bankier0(void* arg);
void * Bankier1(void* arg);
void * Bankier2(void* arg);
void * Bankier3(void* arg);
void * Bankier4(void* arg);


#endif
