#include "stream.h"

stream_t *stream_init(SSL *fd) {
    stream_t *s = malloc(sizeof(stream_t));
    s->pfd = malloc(sizeof(struct pollfd));
    s->pfd->fd = SSL_get_fd(fd);
    s->pfd->events = POLLIN;
    s->handle = fd;
    s->finished = false;
    s->offset = 0;

    return s;
}


size_t stream_peek(stream_t *stream, char *buffer ,size_t num) {

        ssize_t r = 0;
        size_t rthist = num;
         while(true) {

            //int p = poll(stream->pfd, 1, 10000);
//
            //if(p < 1) {
//
//
            //    if(p == 0){
            //        puts("-------timeout -------");
            //        r = -10;
            //        break; /*time out*/
            //    }
            //    if(p < 0)
            //        perror("poll");
            //}

            ssize_t x = SSL_peek(stream->handle, buffer + r, rthist);

            if(x < 1) {
                if(x < 0){
                    perror("stream recv ");
                } else { /** conn close */ }
                break;
            }

            r += x;

            rthist -= x;

            if(rthist <= 0){
                break;
            }

        }

        return r;
}


string_t *stream_read_line(stream_t *stream, char *delim, bool includeDelim) {
    size_t delim_len = strlen(delim);

    string_t *line = string_create();

    size_t buffOffset = 0;


    while(true) {
        char recBuff[50] = {0};
            ssize_t x = stream_read(stream, recBuff, 1);

            if(x == -10) { break; /*due to timeout*/ }

            if(recBuff[0] == delim[0]) {

                char peek_buff[50] = {0};

                size_t s = stream_peek(stream, peek_buff, delim_len - 1);

                if(strncmp(peek_buff, delim + 1, s) == 0) {
                    
                    ssize_t d = stream_read(stream, recBuff + 1, delim_len - 1);

                    if(d == -10) { break; /*due to timeout*/ }

                    if(includeDelim){

                        string_concat(line, recBuff, d + 1);

                        assert(d == (ssize_t)(delim_len - 1));
                    }

                    break;
                }

            }
            
            string_append(line, recBuff[0]);

            buffOffset += x;
        }

        return line;
}


//void read_at_least(stream_t *stream, char *buffer, size_t num);

ssize_t stream_read(stream_t *stream, char *buffer, size_t num) {

        size_t buffOffset = 0;
        size_t toReadNow = num;

        while(true) {
            
            //puts("blockinh on poll");
            //int p = poll(stream->pfd, 1, -1);
//
            //if(p < 1) {
//
//
            //    if(p == 0){
            //        puts("---timeout-----");
            //        buffOffset = -10;
            //        break; /*time out*/
            //    }
            //    if(p < 0)
            //        perror("poll");
            //}

            ssize_t r = SSL_read(stream->handle, buffer + buffOffset, toReadNow);

            if(r < 1) {
                if(r < 0){
                    perror("recv > ");
                }

                break;
            }

            buffOffset += r;

            if(buffOffset == num){
                break;
            }

            if(toReadNow > num) {
                assert(num == toReadNow);
            } else {
                toReadNow -= r;
            }
            
        }
        
        return buffOffset;
}
