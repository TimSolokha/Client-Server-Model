/**
 *  This file handles the server side input in client-server sockets.
 *
 *  Author Tim Solokha
 *  Version 1.0
 *  File: Server.c
 *  Created: Feb 2020
 *  ©Copyright Tim Solokha. All rights reserved.
 *
 *  Description: This class uses socket libraries to enable a connection with a client.
 *  In addition to taking user input, it transforms based on certain phrases typed
 *  into the command line. 
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include<string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 15684
 
const char* transform(char*);

int main()
{
 
    char str[100];
    int listen_fd, comm_fd;
 
    struct sockaddr_in servaddr;
 
    // Listens to specified port
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    // Clears IP Address and Port Number
    bzero( &servaddr, sizeof(servaddr));
 
    // Sets addressing scheme
    servaddr.sin_family = AF_INET;
    // Allows IP to connect
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);
    
    servaddr.sin_port = htons(PORT);
 
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    // Waits for an incoming signal from the client
    listen(listen_fd, 10);
 
    // Continuously waits for client side
    while(1)
    {
        char converted[100];

        comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

        bzero(converted, 100);
 
        read(comm_fd,str,100);

        // Takes the inputted str and transforms it with a custom function
        strcpy(converted, transform(str));
 
        write(comm_fd, converted, strlen(converted)+1);

        close(comm_fd);
 
    }
}

const char* transform(char* inputChar) {

    // Outputs specific message if certain keywords are typed
    if(strcmp(inputChar, "test") == 0) {
        strcpy(inputChar, "Yes, this is a test");
    }
    else if(strcmp(inputChar,"hello") == 0) {
        strcpy(inputChar, "Hello client, nice to see you.");
    }
    else {
        // Any other words inputted will transformed into "meme" casing
        for(int i = 0; i <= strlen(inputChar); i += 2) {
            inputChar[i] = toupper(inputChar[i]);
        }
    }
    return inputChar;
}