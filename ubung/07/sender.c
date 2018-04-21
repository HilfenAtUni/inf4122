
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>


// child >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void sendMessage(char** line, int pid);
void waitForReceived();
static void send_sigusr1(int pid);
static void send_sigusr2(int pid);
static void receive_sigal(int signum);
volatile pthread_condattr_t bitReceived;
volatile pthread_cond_t bitReceivedCond;
volatile pthread_mutex_t c_mutex = PTHREAD_MUTEX_INITIALIZER;

void sendMessage(char** linep, int pid)
{
    char* line = *linep;
    printf("sendMessage -- pid: %d\n", pid);
    // for each character...
    for(int position = 0; position <= strlen(line); position++){
        char nextChar = line[position];
        // for each bit in the character, send it
        for(int charPosition = 0; charPosition < 8; charPosition++){
            if(nextChar & (1 << charPosition)){
                send_sigusr2(pid);
            }else{
                send_sigusr1(pid);
            }
            // wait until it has been received
            waitForReceived();
        }
    }
}

void waitForReceived()
{
    pthread_cond_init(&bitReceivedCond, &bitReceived);
    pthread_cond_wait(&bitReceivedCond, &c_mutex);
    pthread_cond_destroy(&bitReceivedCond);
}

static void send_sigusr1(int pid)
{
    // printf("send --> SIGUSR1\n");
    kill(pid, SIGUSR1);
}

static void send_sigusr2(int pid)
{
    // printf("send --> SIGUSR2\n");
    kill(pid, SIGUSR2);
}

static void receive_sigal(int signum)
{
    switch(signum){
        case SIGUSR1:
        // printf("receive_sigal -- get SIGUSR1\n");
        break;
        case SIGUSR2:
        // printf("receive_sigal -- get SIGUSR1\n");
        break;
    }
    pthread_cond_signal(&bitReceivedCond);
}

// child <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


// parent >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
volatile char message[101];
int position = 0;
char nextChar = 0;
int nextCharPosition = 0;
pthread_condattr_t receiveEnd;
pthread_cond_t receiveEndCond;
pthread_mutex_t p_mutex = PTHREAD_MUTEX_INITIALIZER;

static void handler_p_sig1(int signum, siginfo_t* siginf, void* ptr);
static void handler_p_sig2(int signum, siginfo_t* siginf, void* ptr);
void waitForReceiveEnd();
void signalNext(int pid);

static void incrementCharPos(int pid)
{
    // if we've received a whole byte
    if(++nextCharPosition > 7){
        // if we've received 100 chars, our string always ends (since our string
        // buffer has length 100)
        if(position >= 100){
            nextChar = 0;
        }
        // write received char to the next message position
        message[position++] = nextChar;
        // on end of string, we are done receiving
        if(nextChar == 0){
            signalNext(pid);
            pthread_cond_signal(&receiveEndCond);
            return;
        }else{
            // reset char and charPos
            nextChar = 0;
            nextCharPosition = 0;
        }
    }
    signalNext(pid);
}

static void handler_p_sig1(int signum, siginfo_t* siginf, void* ptr)
{
    // printf("handler_p_sig1 --- signum: %d\n", signum);
    // since nextChar starts with 0, receiving sg1 is equal to advancing the charPos
    incrementCharPos(siginf->si_pid);
}

static void handler_p_sig2(int signum, siginfo_t* siginf, void* ptr)
{
    // printf("handler_p_sig2 --- signum: %d\n", signum);
    // set the next bit to 1, increment position
    nextChar = nextChar | (1 << nextCharPosition);
    incrementCharPos(siginf->si_pid);
}

void waitForReceiveEnd()
{
    // printf("waitForReceiveEnd -- setting for receiving....\n");
    pthread_cond_init(&receiveEndCond, &receiveEnd);
    pthread_cond_wait(&receiveEndCond, &p_mutex);
    pthread_cond_destroy(&receiveEndCond);
}

void signalNext(int pid)
{
    // printf("send next signal by SIGUSR1 to pid(%d)\n", pid);
    kill(pid, SIGUSR1);
}


// parent <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    // -------------------------------------------------------------------
    struct sigaction p_sig1;
    struct sigaction p_sig2;

    memset(&p_sig1, 0, sizeof(p_sig1));
    memset(&p_sig2, 0, sizeof(p_sig2));

    p_sig1.sa_flags = SA_SIGINFO;
    p_sig2.sa_flags = SA_SIGINFO;

    p_sig1.sa_sigaction = handler_p_sig1;
    p_sig2.sa_sigaction = handler_p_sig2;

    sigaction(SIGUSR1, &p_sig1, NULL);
    sigaction(SIGUSR2, &p_sig2, NULL);


    pid_t pid = fork();
    if(0 != pid)
        printf("............. fork ----> child pid: %d\n", pid);
    if(!pid){ //child
        // while(1)
        // {
            pid = getppid();
            char* line = NULL;
            size_t lineLen;
            printf("[child] Please input message:\n");
            while(getline(&line, &lineLen, stdin) == -1 && lineLen <= 0);
            struct sigaction c_sig1;
            memset(&c_sig1, 0, sizeof(c_sig1));
            c_sig1.sa_handler = receive_sigal;
            sigaction(SIGUSR1, &c_sig1, NULL);
            sendMessage(&line, pid);
        // }
    }

    // while(1)
    // {
        waitForReceiveEnd();
        printf("[parent] get: %s\n", message);
    // }

    return EXIT_SUCCESS;
}