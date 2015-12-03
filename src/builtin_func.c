#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "builtin_func.h"

int mysh_cd(char **args)
{
    if (args[1] == NULL) {
        fprintf(stderr, "mysh: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("mysh");
        }
    }
    return 1;
}

int mysh_exit(char **args)
{
    exit(1);
    return 0;
}
