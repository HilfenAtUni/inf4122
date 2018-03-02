#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 5

//struct um die Aktuelle Position im Ausgabe array zu beschreiben.
typedef struct position_ {
	int row;
	int col;
} position_t;

typedef struct position_ * position_p;

// global variables
int matrix[N][N]= {{1,4,5,1,4}, {3,6,1,6,1}, {2,5,8,5,8}, {3,6,1,6,1}, {1,4,5,1,4}};
int outMatrix[N][N]={{0}};

// determine of function
void *square2Thread(void *arg);
void square2();
void printOutMatrix();


void *square2Thread(void *arg)
{
	position_t *data = arg;

	//Multiplikation
	for (int i=0; i<N; ++i)
	{
		int sum = 0;
		for(int n = 0; n< N; n++){
			sum += matrix[data->row][n] * matrix[n][i];
		}
		//Wert an die Position im Ausgabe Array schreiben
		outMatrix[data->row][i] = sum;
		// printf("data->row:%d, i:%d, sum: %d\n", data->row, i, sum);
	}

	pthread_exit(0);
}

void square2()
{
	 for(int i = 0; i < N; i++) {
		//Assign a row and column for each thread
		position_p data = (position_p) malloc(sizeof(position_t));
		if(NULL == data){
			printf("Keine freierspeicher vorhanden");
			return;
		}
		data->row = i;

		// Threads
		pthread_t tid;
		printf("create thread %d\n", i);
		pthread_create(&tid, NULL, square2Thread, data);
		pthread_join(tid, NULL);
	 }
}

void printOutMatrix()
{
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			printf("%4d", outMatrix[i][j]);
		}
		printf("\n");
	 }
}

int main(int argc, char *argv[])
{
	square2();
	printf("Matrix A:\n");
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("Matrix A x A:\n");
	printOutMatrix();

	return EXIT_SUCCESS;
}
