#include "stream.h"

size_t stream_read(stream_t *strm, char *buff, size_t *n){
    size_t rb = 0;
    int total = 0;

    while(1){
        rb = read(strm->handler, buff,n);

        total += rb;

        if(rb == 0)
            break;
        
        if(rb < 0){
            total = -1;
            break;
        }
        

        if(total >= n) break;
    }

    return total;
}

size_t stream_write(stream_t *strm, char *buff, size_t *n){
    size_t wb = 0;
    int total = 0;

    while(1){
        wb = write(strm->handler, buff, n);

        total += wb;

        if(wb == 0)
            break;
        
        if(wb < 0){
            total = -1;
            break;
        }
        

        if(total >= n) break;
    }

    return total;
}

void stream_close(stream_t *strm){
    close(strm->handler);
}

stream_t *stream_create(int sock){
    stream_t *tmp = malloc(sizeof(stream_t));
    tmp->handler = sock;

    return tmp;
}