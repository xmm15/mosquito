#include "connection.h"

connection_t *connection_create(int sock, char *address){
    connection_t *t = malloc(sizeof(connection_t));
    t->sock = sock;
    t->address = address;
    return t;
}

void connection_free(connection_t *c){
    close(c->sock);
    free(c);
}