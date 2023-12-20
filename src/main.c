#include "list.h"
#include <assert.h>

int main(){
    list_t *x = list_create();

    list_pushback(x,"hello");

    assert(strcmp(list_get(x,0), "hello") == 0);
    return 0;
}