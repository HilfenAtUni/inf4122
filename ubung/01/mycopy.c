#define _POSIX_C_SOURCE 200112L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
/*------------------------------------------------------------------------------------------------*/
// add this just for test
#include <assert.h>
/*------------------------------------------------------------------------------------------------*/

void getparams(int argc, char **argv, size_t *buflen, char **inname,
                             char **outname);

void getfilehandles(char *inname, char *outname, int *infd, int *outfd);

void copy(int infd, int outfd, size_t buflen);

int main(int argc, char **argv)
{

    char *inname;
    char *outname;
    size_t buflen;
    int infd;
    int outfd;

    getparams(argc, argv, &buflen, &inname, &outname);
    getfilehandles(inname, outname, &infd, &outfd);

    copy(infd, outfd, buflen);

    if (close(outfd) == -1) {
        perror("Fehler beim Schließen der Ausgabedatei");
        exit(EXIT_FAILURE);
    }

    if (close(infd) == -1) {
        perror("Fehler beim Schließen der Eingabedatei");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, size_t *buflen, char **inname,
                             char **outname)
{
    int opterrflag = 0;
    int opt;

    /* Standard-Wert */
    *buflen = 1;

    /* Kommandozeilenoptionen verarbeiten */
    while ((opt = getopt(argc, argv, "b:")) != -1) {
        switch (opt) {
        case 'b':
            opterrflag = sscanf(optarg, "%zu", buflen) != 1 || *buflen <= 0
                || *buflen >= 1024 * 1024;
            break;
        case '?':
            opterrflag = 1;
            break;
        }
    }

    if (optind < argc) {
        *inname = argv[optind++];
    } else {
        opterrflag = 1;
    }

    if (optind < argc) {
        *outname = argv[optind];
    } else {
        opterrflag = 1;
    }

    if (opterrflag) {
        fprintf(stderr,
                        "Benutzung:\n"
                        "\n"
                        "  %s [-b n] <Eingabedatei> <Ausgabedatei>\n"
                        "\n" "b[=1]: Puffergröße mit 0 < n <= 1024^2\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

void getfilehandles(char *inname, char *outname, int *infd, int *outfd)
{
    //----------------------------------------------------------------------------------------------
    printf("enter function getfilehandles ---->\n");

    // get input file handle by name string of the input file
    *infd = open(inname, O_RDONLY);
    if(*infd == -1) {
        printf("fail to open input file");
        exit(1);
    }

    // get output file handle by name string of the output file
    *outfd = open(outname, O_WRONLY|O_CREAT, S_IWUSR);
    if(*outfd == -1) {
        printf("fail to create output file");
        exit(1);
    }

    printf("infd: %d, outfd: %d\n", *infd, *outfd);
    printf("leave function: getfilehandles <----\n");
    //----------------------------------------------------------------------------------------------
}

void copy(int infd, int outfd, size_t buflen)
{
    //----------------------------------------------------------------------------------------------
    int b_read, b_write;
    char *buffer = (char*)malloc(sizeof(char)*buflen);
    char *ptr;

    printf("enter function: copy ----->\n");
    printf("infd: %d, outfd: %d, buffer[%lu]: %lu\n", infd, outfd, buflen, sizeof(*buffer));

    // assert(buffer!=NULL); // when alloc buffer is not successed, assert this programm

    while(!!(b_read = read(infd, buffer, buflen)))
    {
        if((b_read == -1) && (errno != EINTR)) {
            printf("there is a error while reading data from infd\n");
            break;
        } else if(b_read > 0) {
            ptr = buffer;
            // printf("ready to write to another file\n");
            while(!!(b_write = write(outfd,ptr,b_read)))
            {
                if((b_write == -1) && (errno != EINTR)) {
                    printf("there is a write error.\n");
                    break;
                } else if(b_write == b_read) {
                    break;
                } else if(b_write > 0) {
                    ptr = ptr + b_write;
                    b_read = b_read - b_write;
                }
            }
            if(b_write == -1) {
                break;
            }
        }
    }

    free(buffer);
    printf("leave function: copy <----\n");
    //----------------------------------------------------------------------------------------------
}
