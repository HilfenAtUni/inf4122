#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "deadlock.h"


int main(int argc, char const *argv[])
{
	respool_p rpool = (respool_p)malloc(sizeof(respool_t));
	threadinfo_p P0 = (threadinfo_p)malloc(sizeof(threadinfo_t));
	threadinfo_p P1 = (threadinfo_p)malloc(sizeof(threadinfo_t));
	threadinfo_p P2 = (threadinfo_p)malloc(sizeof(threadinfo_t));
	threadinfo_p P3 = (threadinfo_p)malloc(sizeof(threadinfo_t));
	threadinfo_p P4 = (threadinfo_p)malloc(sizeof(threadinfo_t));
	int errerno;

	rpool->A = 7;
	rpool->B = 2;
	rpool->C = 6;

	P0->pool = rpool;
	P1->pool = rpool;
	P2->pool = rpool;
	P3->pool = rpool;
	P4->pool = rpool;

	P0->A = 0;
	P0->B = 1;
	P0->C = 0;

	P1->A = 4;
	P1->B = 0;
	P1->C = 2;

	P2->A = 3;
	P2->B = 0;
	P2->C = 3;

	P3->A = 3;
	P3->B = 1;
	P3->C = 1;

	P4->A = 0;
	P4->B = 0;
	P4->C = 4;


	P0->pool->B -= 1;
	P0->B -= 1;
	errerno = pthread_create(&(P0->thread), NULL, Bankier0, P0);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_create() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	P1->pool->A -= 2;
	P1->A -= 2;
	errerno = pthread_create(&(P1->thread), NULL, Bankier1, P1);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_create() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	P2->pool->A -= 3;
	P2->pool->C -= 3;
	P2->A -= 3;
	P2->C -= 3;
	errerno = pthread_create(&(P2->thread), NULL, Bankier2, P2);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_create() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	P3->pool->A -= 2;
	P3->pool->B -= 1;
	P3->pool->C -= 1;
	P3->A -= 2;
	P3->B -= 1;
	P3->C -= 1;
	errerno = pthread_create(&(P3->thread), NULL, Bankier3, P3);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_create() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	P4->pool->C -= 2;
	P4->C -= 2;
	errerno = pthread_create(&(P4->thread), NULL, Bankier4, P4);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_create() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}

	errerno = pthread_join(P0->thread, NULL);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_join() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	errerno = pthread_join(P1->thread, NULL);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_join() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	errerno = pthread_join(P2->thread, NULL);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_join() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	errerno = pthread_join(P3->thread, NULL);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_join() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	errerno = pthread_join(P4->thread, NULL);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_join() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}

	free(rpool);
	free(P0);
	free(P1);
	free(P2);
	free(P3);
	free(P4);
	return 0;
}

void * Bankier0(void* arg)
{
	threadinfo_p info = arg;
	respool_p pool = info->pool;

	printf("P0 -- pool A:%d, B:%d, C:%d\n", pool->A, pool->B, pool->C);
	printf("P0 -- need A:%d, B:%d, C:%d\n", info->A, info->B, info->C);

	return 0;
}

void * Bankier1(void* arg)
{
	threadinfo_p info = arg;
	respool_p pool = info->pool;

	printf("P1 -- pool A:%d, B:%d, C:%d\n", pool->A, pool->B, pool->C);
	printf("P1 -- need A:%d, B:%d, C:%d\n", info->A, info->B, info->C);
	return 0;
}

void * Bankier2(void* arg)
{
	threadinfo_p info = arg;
	respool_p pool = info->pool;

	printf("P2 -- pool A:%d, B:%d, C:%d\n", pool->A, pool->B, pool->C);
	printf("P2 -- need A:%d, B:%d, C:%d\n", info->A, info->B, info->C);
	return 0;
}

void * Bankier3(void* arg)
{
	threadinfo_p info = arg;
	respool_p pool = info->pool;

	printf("P3 -- pool A:%d, B:%d, C:%d\n", pool->A, pool->B, pool->C);
	printf("P3 -- need A:%d, B:%d, C:%d\n", info->A, info->B, info->C);
	return 0;
}

void * Bankier4(void* arg)
{
	threadinfo_p info = arg;
	respool_p pool = info->pool;

	printf("P4 -- pool A:%d, B:%d, C:%d\n", pool->A, pool->B, pool->C);
	printf("P4 -- need A:%d, B:%d, C:%d\n", info->A, info->B, info->C);
	return 0;
}
