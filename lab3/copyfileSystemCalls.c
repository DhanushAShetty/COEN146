// Name: Manpreet Sokhi
// Date: April 15, 2020
// Title: Lab assignment 3: Programming UDP/IP socket
// Description: Program to copy files using system calls

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char * argv[]) {
    if (argc < 3) {
        printf("Specify a source. \n");
    }

    int fsrc = open(argv[1], O_RDWR);
    int fdest = open(argv[2], O_RDWR);

    char buffer[100];
    int bytes_read;

    /*
    if (fsrc == NULL) {
        printf("Cannot open src \n");
        exit(1);
    }

    if (fdest == NULL) {
        printf("Cannot open dest \n");
        exit(1);
    }
     */

    while (read(fsrc, &buffer, sizeof(buffer)) ) {
        // bytes_read = read(fsrc, &buffer, sizeof(buffer));
        printf("%s", buffer);
        write(fdest, &buffer, strlen(buffer));

    }

    close(fsrc);
    close(fdest);

    return 0;
}