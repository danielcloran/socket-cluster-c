#include "scclient.c"
#include <stdio.h>
#include <unistd.h>

void _sub_callback(char *channelname, json_object *error, json_object *data) {
    if (error == NULL) {
        printf("Subscribed channel: %s.\n", channelname);
    }
}

void _pub_callback(char *channelname, json_object *error, json_object *data) {
    if (error == NULL) {
        printf("Published to channel: %s.", channelname);
    }
}

void sc_connect(struct socket *s) {
    printf("Successful connected.\n");
    s->subscribe("topic");
}

void disconnect(struct socket *s) {
    printf("Successfully dis-connected.\n");
}

void connect_error(struct socket *s) {
    printf("Connect server error.\n");
}

void on_auth(struct socket *s, bool isauthenticated) {
    printf("Authentication is %s\n", isauthenticated ? "true" : "false");
}

void on_set_auth_token(struct socket *s, char *token) {
    printf("Token has been set.\n");
}

void on_message(char *channelname, json_object *data) {
    printf("%s,%s\n", channelname, json_object_to_json_string(data));
}

int main() {
    s                         = Socket("ws", "localhost", 8000, "/socketcluster/", NULL, -1);
    s->connect_callback       = &sc_connect;
    s->disconnect_callback    = &disconnect;
    s->connect_error_callback = &connect_error;
    s->onauth_callback        = &on_auth;
    s->onauthtoken_callback   = &on_set_auth_token;
    s->on((char *)"rand", &on_message);
    s->onpublish("topic", &on_message);
    s->connect();
}