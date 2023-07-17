/*  
    1. sudo apt install libczmq-dev     -> get library
    2. gcc -o server server.c -lczmq    -> compile
    3. ./server                         -> run
*/

#include <czmq.h>

#include "dataprocess.h"

#define SERVER "tcp://*:5555"

int main(int argc, char **argv)
{
    /* create socket as responder to listen to request */
    zsock_t *responder = zsock_new(ZMQ_REP);

    /* try to open port */
    int r = zsock_bind(responder, SERVER);
    if (r != 5555) {
        printf("FAILED to bind to port\n");
        return 4;
    }

    /* listen to incoming msg */
    while (true) {
        char *msg = zstr_recv(responder);

        /* incoming msg = Low Level, Repsonse with Gang */
        if (!strncmp(msg, "Low Level", MAX_INPUT_BUFFER_SIZE))
            zstr_send(responder, "Gang");

        free(msg);
    }

    /* close socket */
    zsock_destroy(&responder);

    return 0;
}