// Name: Manpreet Sokhi
// Date: April 15, 2020
// Title: Lab assignment 4: File distribution: Client- Server vs. P2P
// Description: UDP client for file transfer

//UDP Client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define SIZE 100

int main() {
    //Declare socket file descriptor. All
    int sockfd;

    //Declare sending buffer of size 1k bytes
    char sbuf[1024];

    //Declare server address
    struct sockaddr_in servAddr;

    //Converts 0
    struct hostent *host;
    host = (struct hostent *) gethostbyname(
            "localhost"); //Local host runs the server. You may use "127.0.0.1": loopback IP address

    //Open a socket, if successful, returns  o

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    //Set the server address to send using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5001);
    servAddr.sin_addr = *((struct in_addr *) host->h_addr);

    int bytes_read;

    //Client to send messages to the server continuously using UDP socket
    while (1) {
        printf("Client: Type a filename to send to Server\n");
        scanf("%s", sbuf);

        FILE *fsrc = fopen(sbuf, "r");
        char buffer[SIZE];
        int bytes_read;

        if (fsrc == NULL) {
            printf("Cannot open src \n");
            exit(1);
        }

        while (!feof(fsrc)) {
            bytes_read = fread(&buffer, 1, 5, fsrc);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &servAddr, sizeof(struct sockaddr));
        }

        fclose(fsrc);
        printf("Done with file!\n");
    }
    return 0;
}