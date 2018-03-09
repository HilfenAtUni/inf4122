#include <stdio.h>
#include <stdlib.h>
unsigned int pages[6]={0};

void aging(int used[6]);
void printPages();
int main(int argc, char const *argv[])
{
  printf("Start: \n");
  printPages();
  int takt1[6]={1,0,1,0,1,1};
  printf("Takt1: \n");
  aging(takt1);
  printPages();
  int takt2[6]={1,1,0,0,1,0};
  printf("Takt2: \n");
  aging(takt2);
  printPages();
  int takt3[6]={1,1,0,1,0,1};
  printf("Takt3: \n");
  aging(takt3);
  printPages();
  int takt4[6]={1,0,0,0,1,0};
  printf("Takt4: \n");
  aging(takt4);
  printPages();
  int takt5[6]={0,1,1,0,0,0};
  printf("Takt5: \n");
  aging(takt5);
  printPages();
}
//Print for Pages bits
void printPages(){
  for(int i=0;i<6;i++){
    printf("Page %d: ",i);
    printf("%c",(pages[i]&0x80?'1':'0'));
    printf("%c",(pages[i]&0x40?'1':'0'));
    printf("%c",(pages[i]&0x20?'1':'0'));
    printf("%c",(pages[i]&0x10?'1':'0'));
    printf("%c",(pages[i]&0x08?'1':'0'));
    printf("%c",(pages[i]&0x04?'1':'0'));
    printf("%c",(pages[i]&0x02?'1':'0'));
    printf("%c",(pages[i]&0x01?'1':'0'));
    printf("\n");
    
  }
}
void aging (int used[6]){
  for(int i=0;i<6;i++){
    pages[i]=pages[i] >> 1; //age
    if(used[i]!=0){
      pages[i]|=0x80;//set most significant bit
    }
  }
}