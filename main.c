#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#define USER_STR_LIM 100

typedef int check_t;
check_t running_p = 1;

void execute();

int main(int argc, char *argv[])
{
  char user_str[USER_STR_LIM];
  while (running_p) {
    printf("$ ");
    if (fgets(user_str, USER_STR_LIM, stdin) == NULL) {
      printf("*** ERROR: something wrong: %s\n", user_str);
      exit(1);
    }
    execute();
    printf("\n");
  }
}

void execute()
{
  char *args[2];
  args[0] = "sleep";
  args[1] = "2";
  args[2] = NULL;

  printf("My Process ID = %d\n", getpid());

  pid_t  pid;
  int    status;
  if ((pid = fork()) < 0) {
    printf("*** ERROR: forking child process failed\n");
    exit(1);
  }
  else if (pid == 0) {
    printf("I am child process...(id = %d)\n", getpid());
    if (execvp(args[0], args) < 0) {
       printf("*** ERROR: exec failed\n");
       exit(1);
    }
  }
  else {
    printf("I am parent process...(id = %d)\n", getpid());
    wait((&status) != pid);
  }
}
