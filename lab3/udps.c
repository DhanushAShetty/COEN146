// Name: Manpreet Sokhi
// Date: April 15, 2020
// Title: Lab assignment 4: File distribution: Client- Server vs. P2P
// Description: UDP server for file transfer

// UDP Server
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char * argv[]) {
    //Declare socket file descriptor. All  
    int sockfd;
    //Declare receiving buffer of size 1k bytes
    char rbuf[1024];

    //Declare server address to which to bind for receiving messages and client address to fill in sending address
    struct sockaddr_in servAddr, clienAddr;
    socklen_t addrLen = sizeof(struct sockaddr);

    //Open a UDP socket, if successful, returns  
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failure to setup an endpoint socket");
        exit(1);
    }

    //Setup the server address to bind using socket addressing structure
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(5001); //Port 5000 is assigned
    servAddr.sin_addr.s_addr = INADDR_ANY; //Local IP address of any interface is assigned (generally one interface IP address)

    //Set address/port of server endpoint for socket socket descriptor
    if ((bind(sockfd, (struct sockaddr *) &servAddr, sizeof(struct sockaddr))) < 0) {
        perror("Failure to bind server address to the endpoint socket");
        exit(1);
    }

    char filename[1024];
    printf("Server: Type a filename to save the messages sent by the Client\n");
    scanf("%s", filename);

    //Sever continuously waits for messages from client, then prints incoming messages.
    while (1) {
        printf("Server waiting for messages from client: \n");
        int nr = recvfrom(sockfd, rbuf, 1023, 0, (struct sockaddr *) &clienAddr, &addrLen);
        rbuf[nr] = '\0';
        printf("Client with IP: %s and Port: %d sent message: %s\n", inet_ntoa(clienAddr.sin_addr),
               ntohs(clienAddr.sin_port), rbuf);
        FILE *fdest = fopen(filename, "a");
        fwrite(rbuf, 1, strlen(rbuf), fdest);
        close(fdest);
    }
    return 0;
}