/**
 *  This file handles the client side input in client-server sockets.
 *
 *  Author Tim Solokha
 *  Version 1.0
 *  File: Client.c
 *  Created: Feb 2020
 *  ©Copyright Tim Solokha. All rights reserved.
 *
 *  Description: This class uses socket libraries to connect to a server. It allows
 *  for user connection to the port 15684, and lets the user use command line arguments. 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 15684
 
int main(int argc,char **argv)
{
    int sockfd,n;
    char sendline[100];
    char recvline[100];
    struct sockaddr_in servaddr;

    if(argc == 1) {

        // Need at least two command line arguments to run program 
        printf("Not enough commands, try again.\n");
    }
    if(argc == 2) {

        // Creates the inital socket for connection
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        bzero(&servaddr,sizeof servaddr);
    
        // Enbales connection to user specified port
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons(PORT);
    
        // Delcaration of the IP address
        inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
    
        // Connect port number to the IP address
        connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    }
 
    // Clears any previous string arguments
    bzero( recvline, 100);

    // Writes, reads, and displays the given string
    write(sockfd,argv[1],strlen(argv[1])+1);
    read(sockfd,recvline,100);
    
    printf("Usage: Modify user inputted string.\n");
    printf("%s\n",recvline);

    // Closes socket in order to prevent broken pipes
    close(sockfd);
 
}