#ifndef GET_TOKENS_H_
#define GET_TOKENS_H_

#define TKN_NORMAL     0
#define TKN_REDIR_IN   1
#define TKN_REDIR_OUT  2
#define TKN_PIPE       3
#define TKN_BG         4
#define TKN_EOL        5
#define TKN_EOF        6
#define TKN_SPC        -1

#define MAX_LEN_OF_TOKEN 100
#define MAX_NUM_OF_TOKEN 20

int is_special_char(char c);
int is_space(char c);
int token_num_of_special_char(char c);
int get_tokens(char *str, char tokens[MAX_NUM_OF_TOKEN][MAX_LEN_OF_TOKEN], int token_nums[MAX_NUM_OF_TOKEN]);

#define MYSH_TOK_BUFSIZE 64
#define MYSH_TOK_DELIM " \t\r\n\a"

typedef struct token_info {
    int token_id;
    char *token;
} TokenInfo;

int mysh_get_tokens(char *line, TokenInfo *token_infos);


#endif
