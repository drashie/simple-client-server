/*  
    1. sudo apt install libczmq-dev     -> get library
    2. gcc -o client client.c -lczmq    -> compile
    3. ./client                         -> run
*/

#include <czmq.h>
#include <stdio.h>
#include <string.h>

#include "dataprocess.h"

#define RASPI_SERVER "tcp://192.168.178.34:5555"
#define LOCAL_SERVER "tcp://localhost:5555"

#define GET_COMMAND 2
#define ADD_COMMAND 3

int main(int argc, char **argv)
{
    char input[MAX_INPUT_BUFFER_SIZE];

    if ((argc < 2) || (argc > ADD_COMMAND)) {
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
    
    /* create socket as requester to connect to server */
    zsock_t *requester = zsock_new(ZMQ_REQ);

    /* connect to server with requester and send data
     * to connect input Ip-Adress of server instead of the raspi connection in my case */
    zsock_connect(requester, RASPI_SERVER);
    zstr_send(requester, input);

    /* wait for the server to response */
    sleep(1);

    /* print out response */
    char *str = zstr_recv(requester);
    printf("%s!", str);

    /* close socket */
    zsock_destroy(&requester);

    return 0;
}