#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid;

    pid = fork();
    if (!pid) {
        chdir("/");
        setsid();
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);

        while(1) {
            sleep(1);
        }
    }
    else {
        printf("%d\n", pid);
        return 0;
    }
}
