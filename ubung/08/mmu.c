#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
 if(argc != 2){
   printf("Use .\\mmu <16bit>");
   return -1;
 }

  
  if(strlen(argv[1])!=16){
   printf("Use .\\mmu <16bit>");
   return -1;  
  }
  char table[16][2]={{010,1},{001,1},{110,1},{000,1},{100,1},{011,1},{000,0},{000,0},{000,0},{101,1},{000,0},{111,1},{000,0},{000,0},{000,0},{000,0}};
  char* input=argv[1];
  unsigned int num=0;
  char offset[12];
  for(int i=0;i<16;i++){
    if(input[i] == '1'){
      if(i<4)  num^= 1<<(3-i);
      else offset[i-4]='1';
    }else if(input[i] =='0'){
      if (i<4) {}//num^= 0<<4-i;
      else offset[i-4]='0';
    }else {
      printf("Use .\\mmu <16bit>");
      return -1;        
    }
  }
  if(table[num][1]==1){
    printf("%d%s \n",table[num][0],offset);
  }else {
    printf("Seitenfehler");
  }
}