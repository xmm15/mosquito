#include <openssl/ssl.h>

unsigned char *base64_encode(unsigned char *str,size_t len);

unsigned char *base64_decode(unsigned char *input,int length);
