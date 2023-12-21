#include "list.h"
#include <assert.h>
#include "stream_server.h"
#include "connection.h"

int main(){
    stream_server_t *s = stream_server_create(10,false,false);

    stream_server_listen(s, 2000);

    while(1){
        connection_t *conn = stream_server_accept(s);
        puts(conn->address);
    }


}