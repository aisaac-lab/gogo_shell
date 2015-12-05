#include <sys/wait.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

void sigtstp_handler_for_child(int p_signame)
{
    printf("===%d\n", getpid());
}

void sigint_handler_for_child(int p_signame)
{
    // exit(1);
}

int mysh_launch(int in, int out, char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        int ctty = open("/dev/tty", O_RDWR);
        setpgid(0, tcgetpgrp(ctty));
        close(ctty);

        if (signal(SIGTSTP, sigtstp_handler_for_child) == SIG_ERR) {
            printf("mysh: something wrong with binding sigtstp_handler_for_child\n");
            exit(1);
        }
        if (signal(SIGINT, sigint_handler_for_child) == SIG_ERR) {
            printf("mysh: something wrong with binding sigint_handler\n");
            exit(1);
        }
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
