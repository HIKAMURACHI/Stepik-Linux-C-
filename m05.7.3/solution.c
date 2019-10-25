#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#define MAXLINE 1000

int cmp_func(const void * a, const void * b)
{
        return *(char *)b - *(char *)a;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    char buf[BUFSIZ];
    int listen_fd, comm_fd;
    int port;

    struct sockaddr_in servaddr;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    bzero( &servaddr, sizeof(servaddr) );

    port = atoi(argv[1]);

    inet_aton("127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listen_fd, 10);

    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);

    while (1) {
        bzero(buf, BUFSIZ);
        read(comm_fd, buf, BUFSIZ);
        if (strncmp("OFF", buf, 3) == 0)
            break;

        qsort(buf, (size_t) strlen(buf), (size_t) sizeof(char), cmp_func);

        write(comm_fd, buf, strlen(buf)+1);
    }

    return 0;
}
