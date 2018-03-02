#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 3

int matrix[N][N]= { {1,4,5}, {2,5,8}, {3,6,1} };
int outMatrix[N][N]={{0}};


//struct um die Aktuelle Position im Ausgabe array zu beschreiben.
struct position{
  int row;
  int col;
};

void *squareThread(void *arg){
   struct position *data = arg;
   int sum = 0;
   //Multiplikation
   for(int n = 0; n< N; n++){
      sum += matrix[data->row][n] * matrix[n][data->col];
   }
   //Wert an die Position im Ausgabe Array schreiben
   outMatrix[data->row][data->col] = sum;

   pthread_exit(0);

}

void square(){
   for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
         //Assign a row and column for each thread
         struct position *data = (struct position *) malloc(sizeof(struct position));
        if(data==NULL){
          printf("Keine freierspeicher vorhanden");
          return;
        }
         data->row = i;
         data->col = j;
         // Threads
         pthread_t tid;
         pthread_create(&tid,NULL,squareThread,data);
         pthread_join(tid, NULL);
      }
   }


}
void printOutMatrix(){
  for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++) {
         printf("%d ", outMatrix[i][j]);
      }
      printf("\n");
   }
}

int main(int argc, char *argv[])
{
  square();
  printOutMatrix();
  return EXIT_SUCCESS;

}
