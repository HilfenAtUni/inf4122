#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include <assert.h>

// #define N 3
#define N 5

//struct um die Aktuelle Position im Ausgabe array zu beschreiben.
typedef struct position_ {
    int row;
    int col;
} position_t;

typedef struct position_ * position_p;

// global variables
// int matrix[N][N]= { {1,4,5}, {2,5,8}, {3,6,1} };
int matrix[N][N]= { {1,4,5,1,4}, {3,6,1,6,1}, {2,5,8,5,8}, {3,6,1,6,1}, {1,4,5,1,4}};
int outMatrix[N][N]={{0}};

// determine of function
void *squareThread(void *arg);
void square();
void printOutMatrix();


void *squareThread(void *arg)
{
    position_t *data = arg;
    int sum = 0;

    //Multiplikation
    for(int n = 0; n< N; n++){
        sum += matrix[data->row][n] * matrix[n][data->col];
    }
    //Wert an die Position im Ausgabe Array schreiben
    outMatrix[data->row][data->col] = sum;

    pthread_exit(0);
}

void square()
{
     for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            //Assign a row and column for each thread
            position_p data = (position_p) malloc(sizeof(position_t));
            if(NULL == data){
                printf("Keine freierspeicher vorhanden");
                return;
            }
            data->row = i;
            data->col = j;

            // Threads
            pthread_t tid;
            printf("create thread %d\n", i*N+j);
            pthread_create(&tid, NULL, squareThread, data);
            pthread_join(tid, NULL);
        }
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
    square();
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
