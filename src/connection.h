#pragma once

#include "stream.h"
//#include "stream_server.h"

typedef struct connection connection_t;
struct connection {
    stream_t *stream;
    char *address;
};

connection_t *connection_create(stream_t *strm, char *addr);
void connection_free(connection_t *c);