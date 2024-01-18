#include "list.h"
#include <assert.h>
#include "stream_server.h"
#include "connection.h"
#include "http.h"
#include "pool.h"
#include "rfc6455.h"

on_message onMessage;

void newMessage(message_t *m) {
    puts("new message received");

    char j[1000] = {0};

    read(m->fd, j, m->message_length);

    buff_t *b = parse_payload(m->mask_start, m->message_length, m->mask, j);

    puts(b->chars);

}

int main(){

    onMessage = newMessage;

    tpool_t *t = tpool_create(5);

    tpool_add_work(t, startChartSystem, NULL);

    stream_server_t *s = stream_server_create(10,true,true);

    stream_server_listen(s, 2000);

    while(1){
        connection_t *conn = stream_server_accept(s);
        
        printf("New connection from %s\n", conn->address);

        char buff[4096] = { 0 };

        int r = recv(conn->sock,buff, 1023,0);


        if(strstr(buff, "\r\n\r\n")){
            map_t *m = parse_http_req(buff);
            map_print(m);
            write_ws_accept(conn,m);
            map_destroy(m);
        }

        if(r == 0){ break; }
        //printf("Haeder size is => ")

        //puts(buff);
    }


}

// int mairn(){
//     buff_t *b = buff_create();
// 
//     buff_concat(b,"hello", 5);
//     buff_concat(b,"hello", 4);
// 
//     buff_print(b);
// }