#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char fstat[255];
    FILE *f;
    int pid, ppid, nowpid;
    char comm[255], state;

    if (argc != 2) {
        printf("Usage: solution PID\n");
        exit(1);
    }

    nowpid = atoi(argv[1]);
    printf("%d\n", nowpid);

    while (nowpid != 1) {
        sprintf(fstat, "/proc/%d/stat", nowpid);
        f = fopen(fstat, "r");
        fscanf(f, "%d %s %c %d ", &pid, comm, &state, &ppid);
        printf("%d\n", ppid);
        nowpid = ppid;
    }

    return 0;
}
