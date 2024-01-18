#include "list.h"
#include <assert.h>
#include "stream_server.h"
#include "connection.h"
#include "http.h"
#include "pool.h"
#include "rfc6455.h"


// declare an extern fn to handle incomming messages
on_message onMessage;


// declare custom message handler
void handleMessage(message_t *m) {
    

    // new message buffe

    char j[1000] = {0};

    // read the full message
    read(m->fd, j, m->message_length);


    // decode message
    buff_t *b = parse_payload(m->mask_start, m->message_length, m->mask, j);


    // dispaly message
    puts(b->chars);


                    // to send to other clients


                    // encode message first
                    buff_t *ms = encode_message(b->chars, b->size, true, 1);

                    for (int j = 0; j < fd_count_g; j++)
                    {
                        int dest_fd = pfds[j].fd;

                            if (send(dest_fd, ms->chars, ms->size, 0) == -1)
                            {
                                perror("send");
                            }
                    }


    // free message
    buff_destroy(b);

}

int main(){

    // how to start an instance


    // set the message handler
    onMessage = handleMessage;

    //start pool
    tpool_t *t = tpool_create(5);


    // branch
    tpool_add_work(t, startChartSystem, NULL);

    // start your http server old thread
    stream_server_t *s = stream_server_create(10,true,true);

    stream_server_listen(s, 2000);

    while(1){
        connection_t *conn = stream_server_accept(s);
        
        printf("New connection from %s\n", conn->address);

        char buff[4096] = { 0 };

        int r = recv(conn->sock,buff, 1023,0);


        if(strstr(buff, "\r\n\r\n")){
            // parse http
            map_t *m = parse_http_req(buff);

            // verify request and add fd to list
            write_ws_accept(conn,m);

            // free map
            map_destroy(m);
        }

        if(r == 0){ break; }
    }


}
