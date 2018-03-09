#include <stdio.h>
#include <stdlib.h>

int cache[3][2]={{4,1},{3,1},{2,1}};
int oldest=0;

int insert(int page);
void printCache();
int main(int argc, char const *argv[])
{
  printf("Start Pages \n");
  printCache();
  printf("Insert 5 \n");
  insert(5);
  printCache();
  printf("Insert 3 \n");
  insert(3);
  printCache();
  printf("Insert 6 \n");
  insert(6);
  printCache();
}
void printCache(){
  for(int i=0;i<3;i++){
    printf("Page: %d RefBit: %d \n",cache[(oldest+i)%3][0],cache[(oldest+i)%3][1]);
  }
}

int insert(int page){
  for (int i=0;i<3;i++){ 
     if(cache[i][0]==page) {   // Hit set ref bit to 1 
       cache[i][1]=1;
       printf("H \n");
       return 1;
     }
  }
  for(int i =0 ; i<3;i++){
    if(cache[(oldest+i)%3][1]==1){ // set ref bit to 0 
      cache[(oldest+i)%3][1]=0;
    }else {                       // found ref bit==0 
      cache[(oldest+i)%3][0]=page;
      cache[(oldest+i)%3][1]=1;
      oldest=oldest+i+1;
      
      printf("PF \n");
      return 0;

    }
   }
    cache[oldest%3][0]=page;
    cache[oldest%3][1]=1;
    oldest=oldest+1;
    
    printf("PF \n");
    return 0;
  
}