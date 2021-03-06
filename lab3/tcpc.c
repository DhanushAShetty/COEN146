// Name: Manpreet Sokhi
// Date: April 15, 2020
// Title: Lab assignment 3: Programming UDP/IP socket
// Description: TCP client for file transfer

//TCP Client
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define SIZE 100

int main(){
//Declare socket file descriptor. All  Unix  I/O  streams  are  referenced  by  descriptors. nr is a declaration of the number of recieved bytes.
int sockfd, nr;

//Declare sending and recieving buffers of size 1k bytes
char sbuf[1024], rbuf[1024];

//Declare server address to connect to
struct sockaddr_in servAddr;
struct hostent *host;

//Converts  domain  names   into  numerical  IP  addresses  via  DNS
host = (struct hostent *)gethostbyname("localhost");

//Open a socket, if successful, returns  a descriptor  associated  with  an endpoint
 if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Failure to setup an endpoint socket");
    exit(1);
 }

//Set the server address to send using socket addressing structure
servAddr.sin_family = AF_INET;
servAddr.sin_port = htons(5000);
servAddr.sin_addr = *((struct in_addr *)host->h_addr);

//Connect to the server
if (connect(sockfd, (struct sockaddr *)&servAddr, sizeof(struct sockaddr))){
    perror("Failure to connect to the server");
    exit(1);
}

int bytes_read;

 //Client begins to write and read from the server
 while(1){
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
         printf("%s", buffer);
         sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servAddr, sizeof(struct sockaddr));
     }
     fclose(fsrc);
     printf("Done with file!\n");
     /*
  printf("Client: Type a message to send to Server\n");
  scanf("%s", sbuf);
  write(sockfd, sbuf, strlen(sbuf));
  read(sockfd, rbuf, 1024);
  printf("Server: sent message: %s\n", rbuf);
  */
 }
 //Close socket descriptor
 close(sockfd);
 return 0;
}
