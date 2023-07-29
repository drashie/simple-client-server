/*  
    1. gcc -o client client.c           -> compile
    2. ./client                         -> run
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "dataprocess.h"

#define RASPI_SERVER "tcp://192.168.178.34:5555"
#define LOCAL_SERVER "tcp://localhost:5555"

#define SERVER_IP   "192.168.178.34"
#define PORT        5555 

#define GET_COMMAND 2
#define ADD_COMMAND 3

int main(int argc, char **argv)
{
    char input[MAX_INPUT_BUFFER_SIZE];

    if ((argc < GET_COMMAND) || (argc > ADD_COMMAND)) { /* not get and not add command == wrong arg*/
        printf("wrong number of arguments!");
        return 5;
    }

    /* arguments are the command for the server request */
    strncpy(input, argv[1], 5);

    if (argc == ADD_COMMAND) { /* add command request to the server */

        if (strlen(argv[2]) > MAX_INPUT_BUFFER_SIZE) {
            printf("input too large!");
            return 6;
        }

        /* create request string */
        strcat(input, " "); 
        strncat(input, argv[2], MAX_INPUT_BUFFER_SIZE);
    } 
    
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[MAX_INPUT_BUFFER_SIZE];

    /* create tcp socket */
    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation failed!");
        exit(EXIT_FAILURE);
    }

    /* connect to the server */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("connection failed!");
        exit(EXIT_FAILURE);
    }

    printf("connected to the server\n");

    /* send data to the server */
    const char *msg = "GET";
    send(clientSocket, msg, strlen(msg), 0);

    /* response from server */
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    buffer[bytesRead] = '\0';
    printf("Recv from server: %s\n", buffer);

    /* close socket */
    close(clientSocket);

    return 0;
}