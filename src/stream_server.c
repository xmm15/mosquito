 #include "stream_server.h"


 stream_server_t *stream_server_create(int backlog, bool reuseAddress,bool reusePort){
    stream_server_t *t = malloc(sizeof(stream_server_t));

    t->backlog = backlog;
    t->reuseAddress = reuseAddress;
    t->reusePort = reusePort;

    t->sockfd = -1;

    return t;
}

void stream_server_listen(stream_server_t *s, size_t port){

    char portstr[10] = {0};

    sprintf(portstr,"%ld", port);

    struct addrinfo hints;
    struct addrinfo *server_info, *p;

    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    // 0 for success
    int status = getaddrinfo(NULL, portstr, &hints, &server_info);

    if (status != 0)
    {
        fprintf(stderr, "Error : %s", gai_strerror(status));
    }

    char address[INET6_ADDRSTRLEN];

    for (p = server_info; p != NULL; p = p->ai_next)
    {

        void *myaddr;

        int family = p->ai_family;

        if (family == AF_INET)
        {
            struct sockaddr_in *myaddress = (struct sockaddr_in *)p->ai_addr;
            myaddr = &(myaddress->sin_addr);
        }
        else if (family == AF_INET6)
        {
            struct sockaddr_in6 *myaddress = (struct sockaddr_in6 *)p->ai_addr;
            myaddr = &(myaddress->sin6_addr);
        }

        inet_ntop(p->ai_family, myaddr, address, INET6_ADDRSTRLEN);


        s->sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if (s->sockfd < 0)
        {
            perror("Socket : ");
        }
        else
        {
            s->address = string_create_copy(address);
            setsockopt(s->sockfd, SOL_SOCKET, SO_REUSEADDR, &s->reuseAddress, sizeof &s->reuseAddress);
                #ifdef SO_REUSEPORT
            setsockopt(s->sockfd, SOL_SOCKET, SO_REUSEPORT, &s->reusePort, sizeof(s->reusePort));
                #endif
            break;
        }
    }

    if (p == NULL)
    {
        fprintf(stderr, "Error creating socket\n");
    }

    if ((status = bind(s->sockfd, p->ai_addr, p->ai_addrlen)) < 0)
    {
        perror("bind");
        exit(1);
    }

    if ((status = listen(s->sockfd, s->backlog)) < 0)
    {
        perror("listen");
    }

}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

connection_t *stream_server_accept(stream_server_t *s){
    struct sockaddr_storage their_address;
    socklen_t len = sizeof their_address;
    
    char address[INET6_ADDRSTRLEN];

    int sock = accept(s->sockfd, (struct sockaddr *)&their_address, &len);

    if(sock < 0){
        perror("socket ");
        return NULL;
    }

    //fcntl(sock, F_SETFL, O_NONBLOCK);

    inet_ntop(their_address.ss_family, get_in_addr((struct sockaddr *)&their_address), address, INET6_ADDRSTRLEN);


    connection_t *conn = connection_create(sock,string_create_copy((char *)inet_ntop(their_address.ss_family, get_in_addr((struct sockaddr *)&their_address), address, INET6_ADDRSTRLEN)));

    return conn;
}

