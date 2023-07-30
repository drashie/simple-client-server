/*  
    1. gcc -o server server.c dataprocess.c             -> compile
    2. ./server                                         -> run
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "dataprocess.h"

#define PORT 5555

int main(int argc, char **argv)
{
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[MAX_INPUT_BUFFER_SIZE];

    /* create tcp socket */
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("failed to create socket!");
        exit(EXIT_FAILURE);
    }
    int enableImmediatReuseOfPort = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enableImmediatReuseOfPort, sizeof(enableImmediatReuseOfPort)) < 0) {
        perror("set socket settings failed!");
        exit(EXIT_FAILURE);
    }

    /* bind to port and ip */
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    if ((bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr))) < 0) {
        perror("binding to port / IP failed!");
        exit(EXIT_FAILURE);
    }
    printf("bound to port: %d\n", PORT);


    if (listen(serverSocket, 1) != -1) {
        /* listen to incoming connections and msg */
        while (true) {
            printf("server is listening on port: %d\n", PORT);
            if ((clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrLen)) < 0) {
                perror("accept connection failed!");
                exit(EXIT_FAILURE);
            }
            printf("client connected: %s\n", inet_ntoa(clientAddr.sin_addr));

            /* recv msg from client */
            int bytesRead;
            if ((bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0)) > 0) {
                buffer[bytesRead] = '\0';
                printf("Received from client: %s\n", buffer);

                const char *response = "Hello from server!";
                send(clientSocket, response, strlen(response), 0);
                close(clientSocket);
            }
        }

        close(serverSocket);

    } else { /* listen is not possible */
        perror("listen failed!");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    /* close socket */
    // zsock_destroy(&responder);

    return 0;
}