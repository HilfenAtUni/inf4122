#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include <assert.h>


int mydir(char *dirname, char param_r);

int main(int argc, char *argv[])
{
    char dirname[256];
    char param_r = 0;
    int opt;
    if (2 < argc)
    {
        while(-1 != (opt = getopt(argc, argv, "r:")))
        {
            if ('r' == opt) {
                param_r = 1;
            }
        }
    }

    // when no parameter, as "."
    if (1 == argc) {
        strcpy(dirname, ".");
    } else if((2 == argc) && (0 == strcmp("-r", argv[1]))){
        strcpy(dirname, ".");
    } else if(0 != strcmp("-r", argv[1])){
        strcpy(dirname, argv[1]);
    } else if ((2 < argc) && (1 != param_r)){
        strcpy(dirname, argv[1]);
    } else {
        strcpy(dirname, argv[2]);
    }

    // chdir(".");

    return mydir(dirname, param_r);
}

int mydir(char *dirname, char param_r)
{
    DIR *dir;
    struct dirent *ent;

    dir = opendir(dirname);
    if (NULL == dir) {
        fprintf(stderr, "unable to opendir %s\n", dirname);
        return 1;
    }

    if (1 == param_r) {
        printf("\n%s:\n", dirname);
    } else {
        printf("\n");
    }

    while (NULL != (ent = readdir(dir))) {
        struct stat buf;

        // through the d_name of entity to find stat information
        lstat(ent->d_name, &buf);

        // only when it is a directory, then display with "/"
        if((4 == ent->d_type) && S_ISDIR(buf.st_mode)){
            // printf("----- %d\n", ent->d_type);
            printf("%s/\n", ent->d_name);
        }else{
            printf("%s\n", ent->d_name);
        }
    }

    // Schleife die Rekursiv durch die Unterordner geht und diese Ausgibt wenn -r gesetzt wurde.
    if(1 == param_r) {
        char curr_path[FILENAME_MAX];

        rewinddir(dir);

        while(NULL != (ent = readdir(dir)))
        {
            struct stat buf;

            strcpy(curr_path, dirname);

            if((0 == strcmp(ent->d_name, ".")) || (0 == strcmp(ent->d_name, ".."))) {
                continue;
            }

            lstat(ent->d_name, &buf);

            if((4 == ent->d_type) && S_ISDIR(buf.st_mode)) {
                strcat(curr_path, "/");
                strcat(curr_path, ent->d_name);
                mydir(curr_path, param_r);
            }
        }

    }

    // close the dir pointer
    closedir(dir);

    return 0;
}
