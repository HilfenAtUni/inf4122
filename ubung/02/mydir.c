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

    while ((ent = readdir(dir)) != NULL) {
        // if (ent->d_name[0] == '.') {
        //     continue;
        // }
        struct stat buf;
        lstat(ent->d_name, &buf);
        // printf("%s: %lu B\n", ent->d_name, buf.st_size);
        if(S_ISDIR(buf.st_mode)){
            printf("%s/\n", ent->d_name);
        }else{
            printf("%s\n", ent->d_name);
        }
        // switch(ent->d_type){
        //     case 4:
        //     {
        //         printf("%s/\n", ent->d_name);
        //         break;
        //     }
        //     case 8:
        //     {
        //         printf("%s\n", ent->d_name);
        //         break;
        //     }
        //     default:
        //     {
        //         break;
        //     }
        // }
    }

    // close the dir pointer
    closedir(dir);
    return 0;
}
