#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_BUF 1024

int main()
{
    /* printf("PID: %d\n", getpid()); */
    int fd1, fd2, res;
    char * myfifo1 = "./in1";
    char * myfifo2 = "./in2";
    char buf[MAX_BUF];
    int result = 0;

    fd_set read_fd_set;

    fd1 = open(myfifo1, O_RDONLY);
    if (fd1 == -1) {
        printf("fd1 == -1\n");
        exit(1);
    }

    fd2 = open(myfifo2, O_RDONLY);
    if (fd2 == -1) {
        printf("fd2 == -1\n");
        exit(1);
    }

    for (;;) {
        /* printf("fd1 = %d, fd2 = %d\n", fd1, fd2); */

        FD_ZERO(&read_fd_set);
        FD_SET(fd1, &read_fd_set);
        FD_SET(fd2, &read_fd_set);
        /* printf("set done\n"); */

        select(5, &read_fd_set, NULL, NULL, NULL);
        if (FD_ISSET(fd1, &read_fd_set)) {
            res = read(fd1, &buf, MAX_BUF);
            if (res > 0) {
                /* printf("read %d bytes from in1: %d\n", res, atoi(buf)); */
                result = result + atoi(buf);
            }
            if (res == 0) {
                /* printf("in1 res == 0\n"); */
                break;
            }
        }
        if (FD_ISSET(fd2, &read_fd_set)) {
            res = read(fd2, &buf, MAX_BUF);
            if (res > 0) {
                /* printf("read %d bytes from in2: %d\n", res, atoi(buf)); */
                result = result + atoi(buf);
            }
            if (res == 0) {
                /* printf("in2 res == 0\n"); */
                break;
            }
        }
    }

    printf("%d\n", result);
    close(fd1);
    close(fd2);

    return 0;
}
