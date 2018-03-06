/*
 * test_mutex.c
 * 1. erzeugen wir einige Thread
 * 2.
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "my_mutex.h"


typedef struct thread_data_ {
	unsigned char lock;
	int pool;
	int flag;
	int pool1;
	int pool2;
} thread_data;

typedef struct thread_data_ * thread_data_p;


void* chkLock(void* arg);
void* chkLock2(void* arg);


int main()
{
	pthread_t thread1;
	pthread_t thread2;
	int errerno;

	thread_data_p data = (thread_data_p)malloc(sizeof(thread_data));
	data->lock = 0;
	data->pool = 0;
	data->flag = 0;
	data->pool1 = 0;
	data->pool2 = 0;

	/* erzeugt zwei thread mit chkLock und chkLock2 */
	errerno = pthread_create(&thread1, NULL, chkLock, data);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_create() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	errerno = pthread_create(&thread2, NULL, chkLock2, data);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_create() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}

	errerno = pthread_join(thread1, NULL);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_join() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}
	errerno = pthread_join(thread2, NULL);
	if(errerno){
		fprintf(stderr, "Fehler - pthread_join() --> %d\n", errerno);
		exit(EXIT_FAILURE);
	}

	printf("pool: %d, flag: %d, pool1: %d, pool2: %d\n",
				data->pool, data->flag, data->pool1, data->pool2);

	exit(EXIT_SUCCESS);
}

void* chkLock(void* arg)
{
	thread_data_p data = arg;

	for(int i=0; i<1000000; i++)
	{
		data->pool1 += 1;
		int tmp = data->flag;
		tmp += 1;
		my_mutex_lock(&(data->lock));
		data->pool += 1;
		my_mutex_unlock(&(data->lock));
		data->flag = tmp;
	}
}

void* chkLock2(void* arg)
{
	thread_data_p data = arg;

	for(int i=0; i<1000000; i++)
	{
		data->pool2 += 1;
		int tmp = data->flag;
		tmp += 1;
		my_mutex_lock(&(data->lock));
		data->pool += 1;
		my_mutex_unlock(&(data->lock));
		data->flag = tmp;
	}
}
