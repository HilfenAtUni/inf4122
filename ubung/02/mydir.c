#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>


int mydir(char *dirname, char param_r);

int main(int argc, char *argv[])
{
    char dirname[256];
    char param_r = 0;
    int opt;
    while ((opt = getopt(argc, argv, "r:")) != -1) {
      if (opt=='r') {
        param_r=1;
        }
     }


    if (argc == 1) { // when no parameter, as "."
        strcpy(dirname, ".");
    } else if (argc >= 2 && !param_r==1){
        strcpy(dirname, argv[1]);
    } else {
      strcpy(dirname,argv[2]);
    }

    return mydir(dirname, param_r);
}


int mydir(char *dirname, char param_r)
{
    DIR *dir;
    struct dirent *ent;
  chdir(dirname);

    dir = opendir(".");
    if (dir == NULL) {
        fprintf(stderr, "unable to opendir %s\n", dirname);
        return 1;
    }

    while ((ent = readdir(dir)) != NULL) {
        struct stat buf;
        lstat(ent->d_name, &buf);
        // printf("%s: %lu B\n", ent->d_name, buf.st_size);
        if(S_ISDIR(buf.st_mode)){
            printf("%s/\n", ent->d_name);

            // add this folder to folder_list
        }else{

            printf("%s\n", ent->d_name);
        }
    }

    // Schleife die Rekursiv durch die Unterordner geht und diese Ausgibt wenn -r gesetzt wurde.
    if(param_r ==1){
      rewinddir(dir);
      char currPath[FILENAME_MAX];
      while ((ent = readdir(dir)) != NULL) {
        strcpy(currPath,"./");
        if(strcmp(ent->d_name,".") && strcmp(ent->d_name,"..")){
        struct stat buf;
        lstat(ent->d_name, &buf);
        // printf("%s: %lu B\n", ent->d_name, buf.st_size);
        if(S_ISDIR(buf.st_mode)){
            if(chdir(strcat(currPath,ent->d_name))== 0){
            printf("\n %s :",currPath);
            mydir(".", param_r);
            chdir("../");
            }else{

            }
        }
        }
      }

    }


    // close the dir pointer
    closedir(dir);
    return 0;
}
