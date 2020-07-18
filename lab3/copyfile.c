// Name: Manpreet Sokhi
// Date: April 15, 2020
// Title: Lab assignment 3: Programming UDP/IP socket
// Description: Program to copy files using functions

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char * argv[]) {
    if (argc < 3) {
        printf("Specify a source. \n");
    }

    FILE *fsrc = fopen(argv[1], "r");
    FILE *fdest = fopen(argv[2], "w");

    char buffer[100];
    int bytes_read;

    if (fsrc == NULL) {
        printf("Cannot open src \n");
        exit(1);
    }

    if (fdest == NULL) {
        printf("Cannot open dest \n");
        exit(1);
    }

    while (!feof(fsrc)) {
        bytes_read = fread(&buffer, 1, sizeof(buffer), fsrc);
        printf("%s", buffer);
        fwrite(&buffer, 1, bytes_read, fdest);

    }

    fclose(fsrc);
    fclose(fdest);

    return 0;
}