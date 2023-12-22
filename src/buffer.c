#include "buffer.h"

buff_t *buff_create()
{
    buff_t *t = malloc(sizeof(buff_t));
    t->chars = malloc(sizeof(unsigned char));
    t->chars[0] = '\0';
    t->size = 0;
    return t;
}

void buff_concat(buff_t *dest, unsigned char *src, size_t len_src)
{
    //['a','b'];
    //len = 2
    dest->chars = realloc(dest->chars, dest->size + len_src + 1);

    for (size_t i = 0; i < len_src; i++)
    {
        dest->chars[dest->size + i] = src[i];
    }

    dest->size += len_src;
}

bool buff_append(buff_t *str, unsigned char c)
{
    if (str != NULL)
    {
        str->chars = realloc(str->chars,str->size + 1);
        str->chars[str->size] = c;

        str->size++;

        if(str->chars){
            return true;
        }
    }

    return false;
}

void buff_print(buff_t *str){
    for(int i = 0; i < str->size; i++){
        printf("%c", str->chars[i]);
    }
    printf("\n");
}

void buff_empty(buff_t *str){
    str->size = 0;
    free(str->chars);
    str->chars = malloc(sizeof(char));
    str->chars[0] = '\0';
}

void buff_destroy(buff_t *str){
    free(str->chars);
    free(str);
    str = NULL;
}