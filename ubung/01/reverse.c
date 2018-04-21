#define _POSIX_C_SOURCE 200112L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
void getparams(int argc, char **argv,  char **inname);


void reverse(char *inname);

int main(int argc, char **argv)
{

    char *inname;

    getparams(argc, argv, &inname);
    //getfilehandles(inname, outname, &infd, &outfd);

    reverse(inname);

    return 0;
}

void getparams(int argc, char **argv, char **inname)
{
    int opterrflag = 0;


    if (optind < argc) {
        *inname = argv[optind++];
        printf("inname: %s\n", *inname);
    } else {
        opterrflag = 1;
    }


    if (opterrflag) {
        exit(EXIT_FAILURE);
    }
}

void reverse (char *inname)
{
    int pos = -1;
    // int filesize;
    int infd;
    int outfd;
    char *revFileName[sizeof(inname)+4];

    strcpy(revFileName, inname);
    strcat(revFileName, ".rev");

    // get infile
    // printf("begin to get inname\n");
    if((infd = open(inname,O_RDONLY)) == -1) {
        printf("fail to open source file");
        exit(1);
    }
    // printf("infd: %p\n", infd);

    // make outfile
    // printf("begin to get outname\n");
    if((outfd = open(revFileName, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1)
    {
        printf("fail to create target file");
        exit(1);
    }
    // printf("outfd: %p\n", outfd);

    int file = infd;
    char buffer[1];

    if(read(file, buffer, 1) != 1)  exit(1);
    // printf(buffer, "\n"); // must not to display content of buffer
    while(lseek(file, pos, SEEK_END) >= 0){
        pos = pos-1; // pos--;
        if(read(file, buffer, 1) != 1)  exit(1);
        write(outfd,buffer,1);
    }

    if (close(outfd) == -1) {
        perror("Fehler beim Schließen der Ausgabedatei");
        exit(EXIT_FAILURE);
    }

    if (close(infd) == -1) {
        perror("Fehler beim Schließen der Eingabedatei");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
