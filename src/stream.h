#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct stream stream_t;

struct stream {
    int handler;
};

size_t stream_read(stream_t *strm, char *buff, size_t *n);

size_t stream_write(stream_t *strm, char *buff, size_t *n);

void stream_close(stream_t *strm);

stream_t *stream_create(int sock);
