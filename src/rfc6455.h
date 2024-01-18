#pragma once

#include <threads.h>
#include "list.h"
#include "map.h"
#include <openssl/ssl.h>
#include <sys/socket.h>
#include <poll.h>
#include <netdb.h>
#include <unistd.h>
#include "base64.h"
#include "http.h"
#include "connection.h"
#include "pool.h"
#include "buffer.h"
#include <fcntl.h>
#include <errno.h>
#include <stream.h>
#include <signal.h>
#include <alloca.h>


extern struct pollfd *pfds;
extern int fd_count_g;
extern int fd_size_g;
extern cnd_t poll_condition;
extern mtx_t poll_mutex;
extern bool keep_chat_alive;
extern list_t *pfd_ids;


#define GUID "258EAFA5-E914-47DA-95CA-C5AB0DC85B11"
#define BUFFER_SIZE 1024

typedef struct message_t message_t;

struct message_t {
    stream_t *stream;
    int final;
    int opcode;
    char *mask;
    int masked;
    int mask_start;
    size_t message_length;
    int fd;
};

void sigAlarmHandler(int sig);

typedef void (*on_message)(message_t *message);

extern on_message onMessage;

bool validate_WS_connection(map_t *request);

char *createAcceptString(char *ws_key);

unsigned int createIntFromByte(unsigned int *bytes, size_t len);

void *get_in_addr_ws(struct sockaddr *sa);

void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);

void del_from_pfds(struct pollfd pfds[], int i, int *fd_count);

int startChartSystem(void *v);

void parse_flags(char *bytes,int *fin, int *opcode , int *mask);

void parse_payload_length(char *bytes, int *payloadLength, int *maskStart);

void parse_masking_key(int mask_start,char *bytes,char *mask_bytes);

buff_t *parse_payload(int maskstart,int pay_load_length,char *mask_key,char *bytes);

buff_t *encode_message(char *message,size_t message_len,bool is_last,unsigned int opcode);

void send_close_frame(char *client_close_message,int sockfd,int pos);

void send_ping_frame(int sockfd);

void send_pong_frame(char *client_client_ping,int sockfd);

void write_ws_accept(connection_t *,map_t *http_req);

void write_ws_decline(connection_t *conn);