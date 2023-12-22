#include "buffer.h"

buff_t *buff_create()
{
    buff_t *t = malloc(sizeof(buff_t));
    t->chars = malloc(sizeof(unsigned char));
    t->size = 0;
    return t;
}

void buff_concat(buff_t *dest, char *src, size_t len_src)
{
    dest->chars = realloc(dest->chars, dest->size + len_src);

    for (size_t i = 0; i < len_src; i++)
    {
        dest->chars[dest->size + i] = src[i];
        //string_append(dest->, src[i]);
    }

    dest->size += len_src;

    //string_append(dest, '\0');
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