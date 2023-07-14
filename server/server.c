/* to build: 

    sudo apt install libczmq-dev

    gcc -o server server.c -lczmq
    ./server 
*/

#include <czmq.h>

int main(int argc, char **argv)
{
    // server, client
    // request, response

    zsock_t *responder = zsock_new(ZMQ_REP);
    int r = zsock_bind(responder, "tcp://*:5555");

    if (r != 5555)
        printf("FAILED to bind to port\n");

    while (true) {
        char *msg = zstr_recv(responder);

        if (!strcmp(msg, "Low Level"))
            zstr_send(responder, "Gang");

        free(msg);
    }

    zsock_destroy(&responder);

    return 0;
}