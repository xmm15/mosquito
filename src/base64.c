#include "base64.h"

unsigned char *base64_encode(unsigned char *str,size_t len)
{
    int pl = 4*((len+2)/3);
    unsigned char *out = calloc(pl+1,1);
    int ol = EVP_EncodeBlock(out,str,len);
    if(pl != ol) return NULL;
    return out;
}


unsigned char *base64_decode(unsigned char *input,int length)
{
    int pl = 3*length/4;
    unsigned char *output = calloc(pl+1,1);
    int ol = EVP_DecodeBlock(output,input,length);
    if(pl != ol) return NULL;
    return output;
}
