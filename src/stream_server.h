#pragma once
#include "stream.h"
#include<stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "_string.h"
#include "connection.h"


typedef struct stream_server stream_server_t;
struct stream_server {
    int backlog;
    int reuseAddress;
    int reusePort;

    int sockfd;

    char *address;
};

void *get_in_addr(struct sockaddr *sa);

stream_server_t *stream_server_create(int backlog, bool reuseAddress,bool reusePort);

connection_t *stream_server_accept(stream_server_t *s);

void stream_server_listen(stream_server_t *s, size_t port);

