#include "connection.h"

connection_t *connection_create(stream_t *strm, char *address){
    connection_t *t = malloc(sizeof(connection_t));
    t->stream = strm;
    t->address = address;
    return t;
}
void connection_free(connection_t *c);