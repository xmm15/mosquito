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

    buff_t *b = parse_payload(m->mask_start, m->message_length, m->mask, j);

    puts ((char *) b->chars);

    buff_t *f = encode_message("echo", 4, true, 1);

    send(m->fd, f->chars, f->size, 0);

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
