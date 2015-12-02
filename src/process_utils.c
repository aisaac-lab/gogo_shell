#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int mysh_launch(int in, int out, char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (in != 0) {
            dup2 (in, 0);
            close (in);
        }
        if (out != 1) {
            dup2 (out, 1);
            close (out);
        }
        if (execvp(args[0], args) == -1) {
            perror("mysh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("mysh");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}
