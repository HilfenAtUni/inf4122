#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int statistics(char *dirname, int *stat_list);

int main(int argc, char *argv[])
{
    char dirname[256];
    int stat_list[8] = {0};


    if (argc == 1) { // when no parameter, as "."
        strcpy(dirname, ".");
    } else {
        strcpy(dirname, argv[1]);
    }

   statistics(dirname, stat_list);
   printf("0 Bytes - 512 Bytes: %d \n", stat_list[0]);
   printf("512 Bytes - 1 KiB: %d \n", stat_list[1]);
   printf("1 KiB - 2 KiB: %d \n", stat_list[2]);
   printf("2 KiB - 4 KiB: %d \n", stat_list[3]);
   printf("4 KiB - 8 KiB: %d \n", stat_list[4]);
   printf("8 KiB - 64 KiB: %d \n", stat_list[5]);
   printf("64 KiB - 1 MiB: %d \n", stat_list[6]);
   printf("Ab 1 MiB: %d \n", stat_list[7]);


}

int statistics(char *dirname, int *stat_list)
{
    DIR *dir;
    struct dirent *ent;
  chdir(dirname);

    dir = opendir(".");


    while ((ent = readdir(dir)) != NULL) {
        // if (ent->d_name[0] == '.') {
        //     continue;
        // }
        struct stat buf;
        lstat(ent->d_name, &buf);

        if(10 == ent->d_type || S_ISDIR(buf.st_mode)){ // link will be ignored
            continue;
        }else if(0<=buf.st_size && 512>buf.st_size){
            // size = "0 KiB";
            stat_list[0] += 1;
        }else if(512<=buf.st_size && 1024>buf.st_size){
            // size
            stat_list[1] += 1;
        }else if(1024<=buf.st_size && (2*1024)>buf.st_size){
            //
            stat_list[2] += 1;
        }else if((2*1024)<=buf.st_size && (4*1024)>buf.st_size){
            //
            stat_list[3] += 1;
        }else if((4*1024)<=buf.st_size && (8*1024)>buf.st_size){
            //
            stat_list[4] += 1;
        }else if((8*1024)<=buf.st_size && (64*1024)>buf.st_size){
            //
            stat_list[5] += 1;
        }else if(64*1024<=buf.st_size && (1024*1024)>buf.st_size){
            //
            stat_list[6] += 1;
        }else if((1024*1024<=buf.st_size)){
            //
            stat_list[7] += 1;
        }
    }
    //Itterieren ueber die Unterordner
   rewinddir(dir);
   char currPath[FILENAME_MAX];
   while ((ent = readdir(dir)) != NULL) {
     strcpy(currPath,"./");
     if(strcmp(ent->d_name,".") && strcmp(ent->d_name,"..")){
      struct stat buf;
      lstat(ent->d_name, &buf);
      if(S_ISDIR(buf.st_mode)){
        if(chdir(strcat(currPath,ent->d_name))== 0){
          statistics(".", stat_list);
          chdir("../");
         }else{

        }
      }
    }
}


    // close the dir pointer
    closedir(dir);
    return 0;
}
