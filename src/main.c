// 61113749 田中和希
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "builtin_func.h"
#include "read_line.h"
#include "get_tokens.h"
#include "parse_cmd.h"
#include "process_utils.h"
#include "file_utils.h"

#define PIPE_READ 0
#define PIPE_WRITE 1

#define NUM_BUILDIN_FUNC 2

char *builtin_str[] = {
    "cd",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &mysh_cd,
    &mysh_exit
};

int
is_next(int token_id, int i, int token_count, TokenInfo *token_infos);

int
is_prev(int token_id, int i, int token_count, TokenInfo *token_infos);

int mysh_execute(int in, int out, char **args)
{
    int i;

    if (args[0] == NULL) return 1;

    for (i = 0; i < NUM_BUILDIN_FUNC; i++) {
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
    int is_running = 1;

    do {
        printf("$ ");
        line = mysh_read_line();

        token_infos = malloc(sizeof(TokenInfo*) * 100);
        int token_count = mysh_get_tokens(line, token_infos);
        int in = STDIN_FILENO;
        int out = -1;
        char **args;
        for (int i=0; i<token_count; i++) {
            TokenInfo token_info = token_infos[i];
            int fd[2];
            pipe (fd);

            if (i == token_count - 1) out = STDOUT_FILENO;

            if (token_info.token_id == TKN_NORMAL) {
                args = malloc(sizeof(char*) * 100);
                args = parse_cmd(token_info.token);
                if (is_next(TKN_PIPE, i, token_count, token_infos)) {
                    out = fd[PIPE_WRITE];
                    mysh_execute(in, out, args);
                    close (fd[PIPE_WRITE]);
                    in = fd[PIPE_READ];
                } else if (is_next(TKN_REDIR_IN, i, token_count, token_infos)) {
                    mysh_execute(open_for_rdir_in(token_infos[i+2].token), out, args);
                    i += 2;
                } else if (is_next(TKN_REDIR_OUT, i, token_count, token_infos)) {
                    printf("%s\n", token_infos[i].token);
                    mysh_execute(in, open_for_rdir_out(token_infos[i+2].token), args);
                    i += 2;
                } else {
                    mysh_execute(in, out, args);
                }
                free(args);
            }
        }

        free(line);
        free(token_infos);
    } while (is_running);
}

int
is_next(int token_id, int i, int token_count, TokenInfo *token_infos)
{
    return (i+1)<token_count && token_infos[i+1].token_id == token_id;
}

int
is_prev(int token_id, int i, int token_count, TokenInfo *token_infos)
{
    return 0<=(i-1) && token_infos[i-1].token_id == token_id;
}

void sigint_handler(int p_signame)
{
    printf("\n");
}

void sigtstp_handler(int p_signame)
{
}


int
main(void)
{
    if (signal(SIGTSTP, sigtstp_handler) == SIG_ERR) {
        printf("mysh: something wrong with binding sigtstp_handler\n");
        exit(1);
    }
    mysh_loop();
    return EXIT_SUCCESS;
}
