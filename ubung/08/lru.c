#include <stdio.h>
#include <stdlib.h>
unsigned int cache[3][2]={{4,0},{3,0},{2,0}};

void aging(int page);
void printPages();
int main(int argc, char const *argv[])
{
  printf("Start: \n");
  printPages();

  aging(3);
  printPages();

  aging(2);
  printPages();

  aging(3);
  printPages();

  aging(5);
  printPages();

  aging(5);
  printPages();
  
  aging(6);
  printPages();
}

//Print for Pages bits
void printPages(){
  for(int i=0;i<3;i++){
    printf("Page %d: ",cache[i][0]);
    printf("%c",(cache[i][1]&0x80?'1':'0'));
    printf("%c",(cache[i][1]&0x40?'1':'0'));
    printf("%c",(cache[i][1]&0x20?'1':'0'));
    printf("%c",(cache[i][1]&0x10?'1':'0'));
    printf("%c",(cache[i][1]&0x08?'1':'0'));
    printf("%c",(cache[i][1]&0x04?'1':'0'));
    printf("%c",(cache[i][1]&0x02?'1':'0'));
    printf("%c ;",(cache[i][1]&0x01?'1':'0'));

    
  }
      printf("\n");
}

void aging (int page){
  int found=0;
  for(int i=0;i<3;i++){ //Hit happens
    if(cache[i][0]==page){
      found=1;
    printf("Zugriff auf %d fuehrt zu H \n",page);
    }
  }
  if(found!=1){ //No hit find minimum
    printf("Zugriff auf %d fuehrt zu PF \n",page);
    int min = 0;
    for (int i=0; i<3 ; i++ ){
      if(cache[i][1]<= cache[min][1]){
        min=i;
      }
    }
    cache[min][1]=0;
    cache[min][0]=page;
    
  }
  for(int i=0; i<3 ;i++){ //age
    cache[i][1]=cache[i][1] >> 1;
    if(cache[i][0]==page){
      cache[i][1]|=0x80;
    }
  }
  
}