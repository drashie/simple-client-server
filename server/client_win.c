#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#include "dataprocess.h"

// compile with: gcc -o cl.exe client_win.c -lws2_32

#define SERVER_IP   "192.168.178.34"
#define PORT        5555 
#define GET_COMMAND 2
#define ADD_COMMAND 3

int main(int argc, char **argv)
{
    char input[MAX_INPUT_BUFFER_SIZE];

    if ((argc < GET_COMMAND) || (argc > ADD_COMMAND)) {
        printf("Wrong number of arguments!");
        return 5;
    }

    strncpy(input, argv[1], 5);

    if (argc == ADD_COMMAND) {

        if (strlen(argv[2]) > MAX_INPUT_BUFFER_SIZE) {
            printf("Input too large!");
            return 6;
        }

        strcat(input, " "); 
        strncat(input, argv[2], MAX_INPUT_BUFFER_SIZE);
    } 
    
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        perror("WSAStartup failed!");
        return 1;
    }

    if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation failed!");
        WSACleanup();
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        perror("Connection failed!");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    printf("Connected to the server\n");

    send(clientSocket, input, strlen(input), 0);

    char *srvMsg = NULL;
    int buffer_size = 150000;
    srvMsg = (char *)malloc(buffer_size);
    if (srvMsg == NULL) {
        perror("Memory allocation failed!");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    Sleep(1000);

    int bytesRead = recv(clientSocket, srvMsg, buffer_size, 0);
    if (bytesRead < 0) {
        perror("Receive failed!");
        free(srvMsg);
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    srvMsg[bytesRead] = '\0';
    printf("Recv from server: %s\n", srvMsg);
    free(srvMsg);

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
