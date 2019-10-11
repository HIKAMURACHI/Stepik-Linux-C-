#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/procfs.h>
#include <sys/types.h>
#include <ctype.h>

int main()
{
    FILE *fp;
    char line[100];
    char *p;

    if ( (fp = fopen("/proc/self/status", "r")) == NULL) {
        fprintf(stderr, "open status file error: %s\n", strerror(errno));
    }
    while(fgets(line, 100, fp)) {
        if(strncmp(line, "PPid:", 5) != 0)
            continue;
        p = line + 6;
        while(isspace(*p)) ++p;

        printf("%s", p);
        break;
    }
    fclose(fp);

    return 0;
}
