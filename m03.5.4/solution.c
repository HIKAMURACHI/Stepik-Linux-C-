#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <regex.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define _REGEX_RE_COMP

void find_in_dir(int proc_pid);

DIR *d;
FILE *f;
struct dirent *e;
regex_t regex;
char fstat[255];
int counter = 1;
int pid, ppid, arg;
char comm[255], state;

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: solution PID\n");
        exit(1);
    }

    if (regcomp(&regex, "^[[:digit:]]", 0) != 0) {
        fprintf(stderr, "Could not compile regex: %s\n", strerror(errno));
        exit(1);
    }
    arg = atoi(argv[1]);
    find_in_dir(arg);

    printf("%d\n", counter);

    return 0;
}

/* Find process with PPID == proc_pid
 * and all him child use recursion.
 */
void find_in_dir(int proc_pid)
{
    DIR *d;
    /* open proc */
    d = opendir("/proc");
    /* read direnr */
    while ((e = readdir(d)) != NULL) {
        /* Check what d_name match pattern */
        if (regexec(&regex, e->d_name, 0, NULL, 0) == 0) {
            /* find_in_dir(atoi(e->d_name)); */
            sprintf(fstat, "/proc/%s/stat", e->d_name);
            f = fopen(fstat, "r");
            fscanf(f,"%d %s %c %d ", &pid, comm, &state, &ppid);
            fclose(f);
            if (proc_pid == ppid) {
                counter++;          /* increase counter */
                find_in_dir(pid);   /* recursion        */
            }
        }
    }
    closedir(d);
}
