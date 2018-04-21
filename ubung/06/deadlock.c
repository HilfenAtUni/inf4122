#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char* bankier(int* existing, int* possessed, int current[5][3], int request[5][3]);
void display_state(int* available,int current[5][3], int request[5][3]);

int main(int argc, char const *argv[])
{
  int existing[3]= {7,2,6};
  int possessed[3]={7,2,6};
	//Werte von Aufgabenblatt
  int currentFirst[5][3]={{0,1,0},{2,0,0},{3,0,3},{2,1,1},{0,0,2}};
  int requestFirst[5][3]={{0,0,0},{2,0,2},{0,0,0},{1,0,0},{0,0,2}};
  char* res;
  printf("First requests \n");
  res=bankier(existing,possessed,currentFirst,requestFirst);
  printf("Status: %s \n", res);
	//request fuer a) unsafe mit max 4 blockierenden Prozessen
  int currentSecond[5][3]={{0,1,0},{2,0,0},{3,0,3},{2,1,1},{0,0,2}};
  int requestSecond[5][3]={{0,0,0},{2,0,2},{2,0,2},{1,0,0},{0,0,2}};
  printf("Second request \n");
  res=bankier(existing,possessed,currentSecond,requestSecond);
  printf("Status: %s \n", res);

	//request fuer b) safe
  int currentThird[5][3]={{0,1,0},{2,0,0},{3,0,3},{2,1,1},{0,0,2}};
  int requestThird[5][3]={{1,0,0},{2,0,2},{0,0,0},{1,0,0},{0,0,2}};
  printf("Third request \n");
  res=bankier(existing,possessed,currentThird,requestThird);
  printf("Status: %s \n", res);
}
void display_state(int* available,int current[5][3], int request[5][3]){
	//avaible print
	printf("available: (%d, %d, %d) \n",available[0],available[1],available[2]);
	//current print
	printf("current: \n");
  for(int i=0;i<5;i++){
    printf("%d, %d, %d \n",current[i][0],current[i][1],current[i][2]);
  }
	//request print
  printf("request: \n");
  for(int i=0;i<5;i++){
    printf("%d, %d, %d \n",request[i][0],request[i][1],request[i][2]);
  }
}


char* bankier(int* existing, int* possessed, int current[5][3], int request[5][3]){
  int available[3];
  int terminated[5]={0};
  int state=0;
	// Berrechnen von available fuer den Start
  for(int i=0;i<3;i++){
  available[i]=existing[i]-possessed[i];
  }
  display_state(available,current,request);
  int sum=0;
  while(sum!=5 && !(state)){
    sum=0;
    state=1;
    for(int i=0;i<5;i++){
			// Testet ob i bereits beendet wurde
      if(terminated[i]){
        sum+=1;
        continue;
      }
      for(int j=0;j<3;j++){
				//prueft ob alle requests (j) von i kleiner als available ist
        if(available[j]<request[i][j]){
          break;
        }
        if(j==2){// Alle requests <= available fuer i
          state=0;
          terminated[i]=1;
          for(int jj=0;jj<3;jj++){
            available[jj]=available[jj]+current[i][jj];//neues available berechnen
          }
        }
      }
    }
  }
  if(sum==5){
    return "safe";
  }else {
    return "unsafe";
  }

}
