#include <stdio.h>

#include "../lib/scclient.c"

void _connect(struct socket *s) {
    printf("successfully connected\n");
}

void disconnect(struct socket *s) {
    printf("successfully dis-connected\n");
}

void connect_error(struct socket *s) {
    printf("successful connect error\n");
}

int main() {
    s                         = Socket((char *)"ws", (char *)"localhost", 8000, (char *)"/socketcluster/", NULL, -1);
    s->connect_callback       = &_connect;
    s->disconnect_callback    = &disconnect;
    s->connect_error_callback = &connect_error;
    // s->ping_str               = (char *)"";
    // s->pong_str               = (char *)"";
    s->connect();
}