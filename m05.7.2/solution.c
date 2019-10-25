#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define BUFLEN 5120

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int sock, port;
    struct sockaddr_in local;
    struct sockaddr remote;
    socklen_t slen = sizeof(remote);
    char buf[BUFLEN];

    port = atoi(argv[1]);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    bind(sock, (struct sockaddr *) &local, sizeof(local));

    while (1) {
        memset(buf, 0, BUFLEN);
        recvfrom(sock, buf, BUFLEN, 0, &remote, &slen);
        if (strncmp("OFF\n", buf, BUFLEN) == 0)
            break;
        else
            buf[BUFLEN - 1] = '\0';
            printf("%s\n", buf);
    }

    return 0;
}
