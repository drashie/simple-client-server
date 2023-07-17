/*  
    1. sudo apt install libczmq-dev     -> get library
    2. gcc -o client client.c -lczmq    -> compile
    3. ./client                         -> run
*/

#include <czmq.h>

#define RASPI_SERVER "tcp://192.168.178.34:5555"
#define LOCAL_SERVER "tcp://localhost:5555"

int main(int argc, char **argv)
{
    /* create socket as requester to connect to server */
    zsock_t *requester = zsock_new(ZMQ_REQ);

    /* connect to server with requester and send data
     * to connect input Ip-Adress of server instead of the raspi connection in my case */
    zsock_connect(requester, RASPI_SERVER);
    zstr_send(requester, "Low Level");

    /* wait for the server to response */
    sleep(1);

    /* print out response */
    char *str = zstr_recv(requester);
    printf("%s!", str);

    /* close socket */
    zsock_destroy(&requester);

    return 0;
}