/* to build: 

    sudo apt install libczmq-dev

     gcc -o client client.c -lczmq
    ./client */

#include <czmq.h>

int main(int argc, char **argv)
{
    zsock_t *requester = zsock_new(ZMQ_REQ);
    zsock_connect(requester, "tcp://localhost:5555");
    zstr_send(requester, "Low Level");

    sleep(1);

    char *str = zstr_recv(requester);
    printf("%s!", str);

    zsock_destroy(&requester);

    return 0;
}