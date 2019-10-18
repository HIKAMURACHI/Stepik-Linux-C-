#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigurg_handler(int signo)
{
    if (signo == SIGURG) {
        exit(0);
    }
}

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

        signal(SIGURG, sigurg_handler);

        while(1) {
            sleep(1);
        }
    }
    else {
        printf("%d\n", pid);
        return 0;
    }
}
