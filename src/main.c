#include "list.h"
#include <assert.h>
#include "stream_server.h"
#include "connection.h"
#include "http.h"
#include "pool.h"
#include "rfc6455.h"

int main(){

    tpool_t *t = tpool_create(5);

    tpool_add_work(t, startChartSystem, NULL);

    stream_server_t *s = stream_server_create(10,false,false);

    stream_server_listen(s, 2000);

    while(1){
        connection_t *conn = stream_server_accept(s);
        
        printf("New connection from %s\n", conn->address);

        char buff[4096] = { 0 };

        recv(conn->sock,buff, 1023,0);

        if(strstr(buff, "\r\n\r\n")){
            map_t *m = parse_http_req(buff);
            write_ws_accept(conn,m);
            map_destroy(m);
        }
        //printf("Haeder size is => ")

        //puts(buff);
    }


}