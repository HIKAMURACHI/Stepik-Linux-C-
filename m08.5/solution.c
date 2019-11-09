#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
    int is_brackets = 0;
    int opindex = 0;
    int opchar = 0;
    char string[] = "Abra-cadabra";
    int lenght = 0;

    struct option opts[] = {
        // set example flag
        {"version", no_argument, 0, 'v'},
        // option args
        {"query", required_argument, 0, 'q'},
        // longname option
        {"longinformationrequest", no_argument, 0, 'i'},
        {0,0,0,0},
    };

    while ((opchar = getopt_long(argc, argv, "vq:i", opts, &opindex)) != -1) {
        switch (opchar) {
            case 'v':
                /* printf("version flag\n"); */
                break;
            case 'q':
                /* lenght = atoi(optarg); */
                /* printf("query=%d\n", lenght); */
                break;
            case 'i':
                /* printf("(c) Harry Potter\n"); */
                break;
            default:
                printf("-\n");
                exit(0);
        }
    }

    printf("+\n");

    return 0;
}
