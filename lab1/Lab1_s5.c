// Name: Manpreet Sokhi
// Date: April 1, 2020
// Title: Lab assignment 1: Unix/Linux Commands and Overview of C Programming
// Description: This program creates a new thread with pthread_create() rather than fork()

/*COEN 146L : Lab1 */
/*Sample C program for Lab assignment 1*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */
#include <pthread.h>

void* myThreadChild (void* nArgs){
    int n =* ((int*)nArgs);
    int i;
    // Child process
    for (i = 0; i < 100; i++) {
        printf("Child process %d\n",i);
        usleep(n);
    }
    return NULL;
}

/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    pthread_t mythread;
    pid_t  pid;
    int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
    int* nArgs = malloc(sizeof(int));
    nArgs[0] = n;

    printf("\n Before forking.\n");
    pthread_create(&mythread, NULL, myThreadChild, (void*) nArgs);
    pthread_create(&mythread, NULL, myThreadChild, (void*) nArgs);
    /*
        // Parent process
        for (i=0;i<100;i++) {
            printf("\t \t \t Parent Process %d \n",i);
            usleep(n);
        }
        */
    pthread_join(mythread, (void*) nArgs);
    return 0;
}

