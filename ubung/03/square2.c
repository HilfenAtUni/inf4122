#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

//struct um die Aktuelle Position im Ausgabe array zu beschreiben.
typedef struct position_ {
    int tid;
    int mask;
    int core_count;
    int matrix_size;
} position_t;

typedef struct position_ * position_p;

#define N 5
// Komplett Aufgabe 3.2
// global variables
int matrix[N][N]= {{1,4,5,1,4}, {3,6,1,6,1}, {2,5,8,5,8}, {3,6,1,6,1}, {1,4,5,1,4}};
int outMatrix[N][N]={{0}};
int idx = 0;

// determine of function
void *square2Thread(void *arg);
void square2(position_p data);
void printOutMatrix();
void cpus();

void *square2Thread(void *arg)
{
    position_t *data = arg;

    for (int i = 0; i < data->matrix_size; ++i)
    {
        int r = ((data->mask>>i) & 0x1);
        if (1 == r)
        {
            for (int jj = 0; jj < data->matrix_size; ++jj)
            {
                int sum = 0;
                for(int n = 0; n< data->matrix_size; n++){
                    sum += matrix[i][n] * matrix[n][jj];
                }
                //Wert an die Position im Ausgabe Array schreiben
                outMatrix[i][jj] = sum;
            }
        }
    }

    pthread_exit(0);
}

void square2(position_p data)
{
    if(NULL == data){
        printf("Keine freier Speicher vorhanden");
        return;
    }

    // Threads
    pthread_t tid;
    printf("create thread %d\n", idx++);
    data->tid += 1;
    pthread_create(&tid, NULL, square2Thread, data);
    pthread_join(tid, NULL);
}

void cpus()
{
    //Assign a row and column for each thread
    position_p data = (position_p) malloc(sizeof(position_t));
    if(NULL == data){
        printf("Keine freier Speicher vorhanden");
        return;
    }

    data->core_count = sysconf(_SC_NPROCESSORS_CONF);
    data->mask = (data->mask & (0x0));
    data->matrix_size = (int)sqrt(sizeof(matrix)/sizeof(int));
    // printf("matrix_size: %d\n", data->matrix_size);

    for (int i = 0; i < data->core_count; ++i)
    {
        for (int j = 0; j < data->matrix_size; ++j)
        {
            if (i == (j%data->core_count)) {
                data->mask = data->mask | (1<<j);
            }
        }
        square2(data);
    }

    free(data);
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
    // square2();
    cpus();
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
