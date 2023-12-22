#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct buff buff_t;
struct buff
{
    int size;
    unsigned char *chars;
};

buff_t *buff_create();

void buff_concat(buff_t *dest, unsigned char *src, size_t len);

void buff_destroy(buff_t *str);

void buff_print(buff_t *str);

void buff_empty(buff_t *str);