/*  
    1. gcc -o client client.c           -> compile
    2. ./client                         -> run
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "dataprocess.h"

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
    send(clientSocket, input, strlen(input), 0);

    /* allocate memory for server response */
    char *srvMsg = NULL;
    int buffer_size = 150000;
    srvMsg = (char *)malloc(buffer_size);
    if (srvMsg == NULL) {
        perror("memory allocation failed!");
        exit(EXIT_FAILURE);
    }
    
    /* wait for the server to response */
    sleep(1);

    /* recv msg from server */
    int bytesRead = recv(clientSocket, srvMsg, buffer_size, 0);
    if (bytesRead < 0) { /* recv failed */
        perror("Receive failed!");
        free(srvMsg);
        exit(EXIT_FAILURE);
    }
    srvMsg[bytesRead] = '\0';
    printf("Recv from server: %s\n", srvMsg);
    free(srvMsg);

    /* close socket */
    close(clientSocket);

    return 0;
}