#pragma once
#include "stream.h"
#include<stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include "_string.h"


typedef struct stream_server stream_server_t;
struct stream_server {
    int backlog;
    int reuseAddress;
    int reusePort;

    int sockfd;

    char *address;
};

stream_server_t *stream_server_create(int backlog, bool reuseAddress,bool reusePort);

