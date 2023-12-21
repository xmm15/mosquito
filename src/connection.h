#pragma once

//#include "stream_server.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct connection connection_t;
struct connection {
    int sock;
    char *address;
};

connection_t *connection_create(int sock, char *addr);
void connection_free(connection_t *c);