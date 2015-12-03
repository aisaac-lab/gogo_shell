#ifndef BUILDIN_FUNCS_H_
#define BUILDIN_FUNCS_H_

int mysh_num_builtins(void);
int mysh_cd(char **args);
int mysh_exit(char **args);

char *builtin_str[];
int (*builtin_func[]) (char **);

#endif
