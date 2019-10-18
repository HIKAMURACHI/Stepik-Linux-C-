#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s programm arg\n", argv[0]);
        exit(1);
    }

    pid_t pid;
    int status;
    int pipefd[2];
    int counter = 0;

    pipe(pipefd);

    if ((pid = fork()) < 0) {
        fprintf(stderr, "Can't fork: %s\n", strerror(errno));
        exit(1);
    } else if (pid == 0) {
        /* child here */
        close(pipefd[0]);
        dup2(pipefd[1], 1); // send stdout to the pipe
        close(pipefd[1]);   // this descriptor is no longer needed
        execl(argv[1], argv[1], argv[2], NULL);
    } else {
        close(pipefd[1]);  // close the write end of the pipe in the paren
        char buffer[4096];
        int bytes;

        while ((bytes = read(pipefd[0], buffer, sizeof(buffer))) != 0) {
            /* printf("read %d bytes\n", bytes); */
            int i = 0;
            for (i = 0; i < bytes; i++) {
                if (buffer[i] == '0')
                    counter = counter + 1;
            }
        }
        /* parrent */
        if (waitpid (pid, &status, 0) != pid) {
            fprintf(stderr, "waitpid error: %s\n", strerror(errno));
            exit(1);
        }

        printf("%d\n", counter);
    }

    return 0;
}
