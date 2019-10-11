#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <regex.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define _REGEX_RE_COMP

int main()
{
    DIR *d;
    FILE *f;
    struct dirent *e;
    regex_t regex;
    char fstat[255];
    int counter = 0;
    int pid, ppid;
    char comm[255], state;


    if (regcomp(&regex, "^[[:digit:]]", 0) != 0) {
        fprintf(stderr, "Could not compile regex: %s\n", strerror(errno));
        exit(1);
    }

    d = opendir("/proc");
    while ((e = readdir(d)) != NULL) {
        /* printf("%s", e->d_name); */
        if (regexec(&regex, e->d_name, 0, NULL, 0) == 0) {
            /* printf("%s match\n", e->d_name); */
            sprintf(fstat, "/proc/%s/stat", e->d_name);
            /* printf("fstat: %s\n", fstat); */
            f = fopen(fstat, "r");
            fscanf(f,"%d %s %c %d ", &pid, comm, &state, &ppid);
            if (strcmp("(genenv)", comm) == 0)
                counter = counter + 1;
        }
    }
    closedir(d);
    printf("%d\n", counter);

    return 0;
}
