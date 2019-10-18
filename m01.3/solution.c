#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <inttypes.h>

int main(int argc, char **argv)
{
    void *handle;
    int (*func)(int);
    char *error;
    char libname[200];

    if (argv[1][0] != '/') {
        sprintf(libname, "./%s", argv[1]);
    }
    else {
        sprintf(libname, "%s", argv[1]);
    }
    handle = dlopen(libname, RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    func = dlsym(handle, argv[2]);
    if ((error = dlerror()) != NULL) {
        fputs(error, stderr);
        exit(1);
    }

    /* int i = (intptr_t)argv[3]; */
    int i = atoi(argv[3]);
    printf("%d\n", (*func)(i));
    dlclose(handle);
}
