#ifndef PARSE_CMD_H_
#define PARSE_CMD_H_
char **parse_cmd(char *cmd_line);
#define MYSH_TOK_BUFSIZE 64
#define MYSH_TOK_DELIM " \t\r\n\a"
#endif
