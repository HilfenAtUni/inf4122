#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include <sys/stat.h>


int mydir(char *dirname);

int main(int argc, char *argv[])
{
    char dirname[256];

    if (argc == 1) { // when no parameter, as "."
        strcpy(dirname, ".");
    } else {
        strcpy(dirname, argv[1]);
    }


    return mydir(dirname);
}


int mydir(char *dirname)
{
    DIR *dir;
    struct dirent *ent;

    dir = opendir(dirname);
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
        }else{
            printf("%s\n", ent->d_name);
        }
    }

    // close the dir pointer
    closedir(dir);
    return 0;
}
