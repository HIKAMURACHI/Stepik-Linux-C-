#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
        return -1;

    int i;
    struct hostent *h;
    struct in_addr **addr_list;

    h = gethostbyname(argv[1]);
    if (!h) {
        fprintf(stderr, "gethostbyname: %s\n", strerror(errno));
        exit(1);
    }

    addr_list = (struct in_addr **)h->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("%s\n", inet_ntoa(*addr_list[i]));
    }

    return 0;
}
