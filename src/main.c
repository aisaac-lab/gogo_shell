#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "read_line.h"
#include "get_tokens.h"
#include "parse_cmd.h"
#include "process_utils.h"

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define PIPE_READ 0
#define PIPE_WRITE 1

int mysh_cd(char **args);
int mysh_help(char **args);
int mysh_exit(char **args);

int
is_next_pipe(int i, int token_count, TokenInfo *token_infos);

char *builtin_str[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &mysh_cd,
    &mysh_help,
    &mysh_exit
};

int mysh_num_builtins() {
    return sizeof(builtin_str) / sizeof(char *);
}

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

int mysh_help(char **args)
{
    int i;
    printf("Stephen Brennan's mysh\n");
    printf("Type program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < mysh_num_builtins(); i++) {
        printf("  %s\n", builtin_str[i]);
    }

    printf("Use the man command for information on other programs.\n");
    return 1;
}

int mysh_exit(char **args)
{
    return 0;
}


int mysh_execute(int in, int out, char **args)
{
    int i;

    if (args[0] == NULL) return 1;

    for (i = 0; i < mysh_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    return mysh_launch(in, out, args);
}

void mysh_loop(void)
{
    char *line;
    TokenInfo *token_infos;
    int status;

    do {
        printf("$ ");
        line = mysh_read_line();

        token_infos = malloc(sizeof(TokenInfo*) * 100);
        int token_count = mysh_get_tokens(line, token_infos);
        int in = STDIN;
        int out = -1;
        char **args;
        for (int i=0; i<token_count; i++) {
            TokenInfo token_info = token_infos[i];
            int fd[2];
            pipe (fd);

            if (i == token_count - 1) out = STDOUT;

            if (token_info.token_id == TKN_NORMAL) {
                args = malloc(sizeof(char*) * 100);
                args = parse_cmd(token_info.token);
                if (is_next_pipe(i, token_count, token_infos)) {
                    out = fd[PIPE_WRITE];
                    status = mysh_execute(in, out, args);
                    close (fd[PIPE_WRITE]);
                    in = fd [PIPE_READ];
                } else {
                    status = mysh_execute(in, out, args);
                }
                free(args);
            }
        }

        free(line);
        free(token_infos);
    } while (status);
}

int
is_next_pipe(int i, int token_count, TokenInfo *token_infos)
{
    return (i+1)<token_count && token_infos[i+1].token_id == TKN_PIPE;
}

int
is_prev_pipe(int i, int token_count, TokenInfo *token_infos)
{
    return 0<=(i-1) && token_infos[i-1].token_id == TKN_PIPE;
}

int
main(void)
{
    mysh_loop();
    return EXIT_SUCCESS;
}
