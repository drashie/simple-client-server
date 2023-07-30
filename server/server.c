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

/**
 * @brief process msg received from client
 *        and return server response depending
 *        on the found command
 * @param msg from client
 * @return response depending on msg command 
 */
char* msg_processing(char* msg)
{
    char *output = NULL;
    if (!strncmp(msg, "GET", MAX_INPUT_BUFFER_SIZE))
        output = get_data_content();
    else if ((strlen(msg) < MAX_INPUT_BUFFER_SIZE) && (strstr(msg, "ADD"))) {
        char line[MAX_INPUT_BUFFER_SIZE];
        strcpy(line, (msg + 4)); /* cut the add command from the string */

        if (!write_data_content(line)) /* try to add the line to the string */
            output = strdup("LINE SUCCESSFULLY ADDED");
        else {
            perror("failed to write to file!");
            exit(EXIT_FAILURE);
        }
    } else 
        output = strdup("ERROR: UNKNOWN CMD!");
    return output;
}

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
    /* allow immediat reuse of ip/port after process termination */
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

                char *resp = msg_processing(buffer);
                send(clientSocket, resp, strlen(resp), 0);
                free(resp);
                printf("buffer freed!\n");
            }
            close(clientSocket);
        }
        close(serverSocket);

    } else { /* listen is not possible */
        perror("listen failed!");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    return 0;
}