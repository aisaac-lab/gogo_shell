#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#include <errno.h>

#include "stream_utils.h"
#include "get_tokens.h"

#define USER_STR_LIM 100
#define STDIN 0
#define STDOUT 1
#define STDERR 2

typedef int check_t;
check_t running_p = 1;

void execute_cmd(char *args[], int from_pipe, int to_pipe);

int pfd[2];
int e_pfd[2];
#define READ  (0)
#define WRITE (1)

void
init_shared_pip(void)
{
    if (pipe(pfd) < 0) {
        perror("pipe");
        close(pfd[READ]);
        close(pfd[WRITE]);
        exit(-1);
    }

    if (pipe(e_pfd) < 0) {
        perror("pipe");
        close(pfd[READ]);
        close(pfd[WRITE]);
        exit(-1);
    }
}

int
main(int argc, char *argv[])
{
    char *user_str;
    // int fd;
    // char filename[80];
    // char *user_str = "ls -al | sdfkjfj < | > sdfjdf &";
    // int po;
    // while(user_str[po]) {
    //     printf("%c\n", user_str[po]);
    //     po++;
    // }

    // while (running_p) {
    //     printf("$ ");
    //     if (fgets(user_str, USER_STR_LIM, stdin) == NULL) {
    //         printf("*** ERROR: something wrong: %s\n", user_str);
    //         exit(1);
    //     }
    //     char *args1[2] = { "ls", NULL };
    //     char *args2[3] = { "grep", "m", NULL };
    //
    //     // execute_with_pipe(args1, args2);
    //     chdir("/");
    //     execute_cmd(args1);
    //     printf("\n");
    // }
    init_shared_pip();
    chdir("/");
    char *args1[2] = { "ls", NULL };
    char *args2[3] = { "gredp", "m", NULL };

    stream_utils_write("send from child", pfd[WRITE]);
    stream_utils_read(pfd[READ]);


    execute_cmd(args1, 0, 1);
    // stream_utils_attach_skt(pfd[WRITE], STDERR);
      // fprintf(stderr, "2\n");
    // execute_cmd(args2, 0, 0);
    // stream_utils_read(pfd[READ]);
    // stream_utils_read(STDIN);


    stream_utils_read(e_pfd[READ]);

    char *str = "ls -al   |   grep   a > <";
    int token_nums[MAX_NUM_OF_TOKEN];
    char tokens[MAX_NUM_OF_TOKEN][MAX_LEN_OF_TOKEN];
    int count_of_tokens = get_tokens(str, tokens, token_nums);

    for (int i=0; i<count_of_tokens; i++) {
        printf("%d\n", token_nums[i]);
        printf("%s\n", tokens[i]);
    }

    // close(STDIN);
    // init_shared_pip();

    // dup2(pfd[READ], STDIN);
    // char s;
    // s = getc(STDIN);
    // fprintf(stdout, "エラー: ファイルがオープンできません: %s\n", "sss");


    // execute_with_pipe(args1, args2);
}

void
execute_cmd(char *args[], int from_pipe, int to_pipe)
{
    pid_t pid;
    int   status;
    if ((pid = fork()) < 0) {
        printf("*** ERROR: forking child process failed\n");
        exit(-1);
    }
    else if (pid == 0) {
        if (to_pipe)   stream_utils_attach_skt(pfd[WRITE], STDOUT);
        if (from_pipe) stream_utils_attach_skt(pfd[READ], STDIN);

        stream_utils_attach_skt(e_pfd[WRITE], STDERR);
        fprintf(stderr, "エラー: ファイルがオープンできません\n");
        if (execvp(args[0], args) < 0) {
            printf("*** ERROR: exec failed\n");
            exit(1);
        }
    }
    else {
        wait(&status);
    }
}
