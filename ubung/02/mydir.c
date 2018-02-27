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

void getparams(int argc, char **argv, size_t *buflen, char **inname);

void getfilehandles(char *inname, int *infd);

void mydir(int infd);

int main(int argc, char **argv)
{

    char *inname;
    size_t buflen;
    int infd;

    getparams(argc, argv, &buflen, &inname);
    getfilehandles(inname, &infd);

    mydir(infd);

    if (close(infd) == -1) {
        perror("Fehler beim Schließen der Eingabedatei");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

void getparams(int argc, char **argv, size_t *buflen, char **inname)
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

    if (opterrflag) {
        fprintf(stderr,
                        "Benutzung:\n"
                        "\n"
                        "  %s [-b n] <Eingabedatei> <Ausgabedatei>\n"
                        "\n" "b[=1]: Puffergröße mit 0 < n <= 1024^2\n", argv[0]);
        exit(EXIT_FAILURE);
    }
}

void getfilehandles(char *inname, int *infd)
{
    //----------------------------------------------------------------------------------------------
    printf("enter function getfilehandles ---->\n");

    // get input file handle by name string of the input file
    *infd = open(inname, O_RDONLY);
    if(*infd == -1) {
        printf("fail to open input file");
        exit(1);
    }

    printf("inname: %p, infd: %d\n", inname, *infd);
    printf("leave function: getfilehandles <----\n");
    //----------------------------------------------------------------------------------------------
}

void mydir(int infd)
{
    printf("enter function mydir --->\n");
    // do here....
    printf("leave function mydir <---\n");
}
