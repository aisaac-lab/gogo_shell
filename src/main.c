#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define USER_STR_LIM 100
#define STDIN 0
#define STDOUT 1
#define STDERR 2

typedef int check_t;
check_t running_p = 1;

void execute_to_pip(char *args[]);
void execute_from_pip(char *args[]);
void execute_cmd(char *args[]);

#define TKN_NORMAL     0
#define TKN_REDIR_IN   1
#define TKN_REDIR_OUT  2
#define TKN_PIPE       3
#define TKN_BG         4
#define TKN_EOL        5
#define TKN_EOF        6

int pfd[2];
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
}

void
pry_write(char *mes, int fd)
{
    write(fd, mes, strlen(mes));
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
    char *args2[3] = { "grep", "m", NULL };
    printf("%d\n", pfd[0]);
    pry_write("send from child", pfd[WRITE]);


    execute_to_pip(args1);
    // char buf[128];
		// read(pfd[0], buf, sizeof(char) * 128);
		// printf("child=[%s]\n", buf);
    // close(STDIN);
    init_shared_pip();
    char buf[128];
    read(pfd[0], buf, sizeof(char) * 128);
    printf("child=[%s]\n", buf);
    // dup2(pfd[READ], STDIN);
    // char s;
    // s = getc(STDIN);
    // fprintf(stdout, "エラー: ファイルがオープンできません: %s\n", "sss");


    // execute_with_pipe(args1, args2);
}

void
execute_to_pip(char *args[])
{
    pid_t pid;
    int   status;
    if ((pid = fork()) < 0) {
        printf("*** ERROR: forking child process failed\n");
        exit(-1);
    }
    else if (pid == 0) {
        close(STDOUT);
        dup2(pfd[WRITE], STDOUT);
        close(pfd[WRITE]);
        if (execvp(args[0], args) < 0) {
             printf("*** ERROR: exec failed\n");
             exit(1);
        }
    }
    else {
        wait(&status);
    }
}

void
execute_from_pip(char *args[])
{
    pid_t pid;
    int   status;
    char *user_str;
    if ((pid = fork()) < 0) {
        printf("*** ERROR: forking child process failed\n");
        exit(-1);
    }
    else if (pid == 0) {
        close(STDIN);
        dup2(pfd[READ], STDIN);
        char *s;
        scanf("%s", s);
        fprintf(stdout, "エラー: ファイルがオープンできません: %s\n", "sss");
        // char c;
        // c = getc(STDIN);
        // printf("%c\n", c);
        // char buf[128];
    		// read(pfd[0], buf, sizeof(char) * 128);
    		// printf("child=[%s]\n", buf);
    }
    else {
        wait(&status);
    }
}
// void execute_with_pipe(char *args[], char *args2[])
// {
//     pid_t  pid;
//     int    stat1, stat2;
//
//     if (fork() == 0) {
        // close(STDOUT);
        // dup2(pfd[WRITE], STDOUT);
        // close(pfd[READ]); close(pfd[WRITE]);
        // execvp(args1[0], args1);
//     }
//     if (fork() == 0) {
        // close(STDIN);
        // dup2(pfd[READ], STDIN);
        // close(pfd[READ]); close(pfd[WRITE]);
        // execvp(args2[0], args2);
//     }
//     close(pfd[READ]); close(pfd[WRITE]);
//     wait(&stat1); wait(&stat2);
//   // kill(getpid(), 9);
// }

void execute_cmd(char *args[])
{
    pid_t pid;
    int   status;
    if ((pid = fork()) < 0) {
        perror("pipe");
        exit(-1);
    }
    else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
             printf("*** ERROR: exec failed\n");
             exit(1);
        }
    }
    else {
        wait(&status);
    }
}
