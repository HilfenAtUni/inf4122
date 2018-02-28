#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include <sys/stat.h>

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *ent;
    char dirname[256];

    if (argc == 1) {
        strcpy(dirname, ".");
    } else {
        strcpy(dirname, argv[1]);
    }

    dir = opendir(dirname);
    if (dir == NULL) {
        fprintf(stderr, "unable to opendir %s\n", dirname);
        return 1;
    }

    int stat_list[8] = {0};
    while ((ent = readdir(dir)) != NULL) {
        // if (ent->d_name[0] == '.') {
        //     continue;
        // }
        struct stat buf;
        lstat(ent->d_name, &buf);

        if(10 == ent->d_type){ // link will be ignored
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
        if(S_ISDIR(buf.st_mode)){
            // printf("%s/\n", ent->d_name);
            printf("[%d] %s/:\t\t%8lu B\n", ent->d_type, ent->d_name, buf.st_size);
        }else{
            // printf("%s\n", ent->d_name);
            printf("[%d] %s:\t\t%8lu B\n", ent->d_type, ent->d_name, buf.st_size);
        }
    }

    for (int i = 0; i < 8; ++i)
    {
        printf("%d ", stat_list[i]);
    }

    // close the dir pointer
    closedir(dir);
    return 0;
}
