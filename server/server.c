/*  
    1. sudo apt install libczmq-dev                     -> get library
    2. gcc -o server server.c dataprocess.c -lczmq      -> compile
    3. ./server                                         -> run
*/

#include <czmq.h>
#include <stdio.h>
#include <string.h>

#include "dataprocess.h"

#define SERVER "tcp://*:5555"

int main(int argc, char **argv)
{
    /* create socket as responder to listen to request */
    zsock_t *responder = zsock_new(ZMQ_REP);
    printf("main fn started!\n");

    /* try to open port */
    int r = zsock_bind(responder, SERVER);
    if (r != 5555) {
        printf("FAILED to bind to port\n");
        return 4;
    }
    printf("port is bound to %d\n", r);

    /* listen to incoming msg */
    while (true) {
        char *msg = zstr_recv(responder);
        printf("listening for msgs\n");
        
        if (msg != NULL) {
            printf("Recv Msg: %s\n", msg);
            if (!strncmp(msg, "GET", MAX_INPUT_BUFFER_SIZE)) {
                char *output = get_data_content();
                zstr_send(responder, output);
                free(output);
            } else if ((strlen(msg) < MAX_INPUT_BUFFER_SIZE) && (strstr(msg, "ADD"))) { 
                char line[MAX_INPUT_BUFFER_SIZE];
                strcpy(line, (msg + 4)); /* Cut the ADD cmd from the given string */

                if (!write_data_content(line)) /* try to add the line to the txt file */
                    zstr_send(responder, "LINE SUCCESFULLY ADDED");
            } else {
                printf("Unknown Command!: %s\n", msg);
                zstr_send(responder, "ERROR: UNKNOWN CMD!");
            }
        }

        free(msg);
    }

    /* close socket */
    zsock_destroy(&responder);

    return 0;
}