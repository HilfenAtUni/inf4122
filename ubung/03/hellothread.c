#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

static void *threadRunning (){
  printf("new thread running \n");

  return 0;
}

int main(int argc, char *argv[])
{
  pthread_t thread;

  printf("main() \n");

  pthread_create(&thread, NULL,&threadRunning, NULL);

  pthread_join(thread, NULL);
  printf("thread finished \n");

  return EXIT_SUCCESS;

}
