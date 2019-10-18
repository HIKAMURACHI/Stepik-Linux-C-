#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int usr1 = 0;
int usr2 = 0;

void usr1_handler(int signo)
{
    if (signo == SIGUSR1)
        usr1 = usr1 + 1;
}

void usr2_handler(int signo)
{
    if (signo == SIGUSR2)
        usr2 = usr2 + 1;
}

void term_handler(int signo)
{
    if (signo == SIGTERM) {
        printf("%d %d\n", usr1, usr2);
        exit(0);
    }
}

int main()
{
    signal(SIGUSR1, usr1_handler);
    signal(SIGUSR2, usr2_handler);
    signal(SIGTERM, term_handler);

    while(1) {}

    return 0;
}
