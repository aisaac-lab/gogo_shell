#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "get_tokens.h"

int
mysh_get_tokens(char *line, TokenInfo *token_infos)
{
    int len_of_str = strlen(line);
    int count_of_tokens = 0;
    for (int i=0; i<len_of_str; i++) {
        char *token;
        int token_id;
        token = malloc(sizeof(char*));
        char current_char = line[i];
        printf("===%c\n", current_char);
        if (is_special_char(current_char)) {
            token_id = token_num_of_special_char(current_char);
            token[0] = current_char;
        } else if (is_space(current_char)) {
        } else  {
            int current_i = i;
            for (; i<len_of_str && !is_special_char(line[i]); i++){
                token[i-current_i] = line[i];
            }
            i--;
            token_id = TKN_NORMAL;
        }

        if (token_id != TKN_SPC) {
            TokenInfo token_info = { token_id, token };
            token_infos[count_of_tokens] = token_info;
            count_of_tokens++;
        }
    }
    return count_of_tokens;
}

int
is_special_char(char c)
{
    return (c == '<' || c == '>' || c == '|' || c == '&');
}

int
is_space(char c)
{
    return (c == ' ');
}

int
token_num_of_special_char(char c)
{
    switch (c) {
      case '<':
          return TKN_REDIR_IN;
      case '>':
          return TKN_REDIR_OUT;
      case '|':
          return TKN_PIPE;
      case '&':
          return TKN_BG;
      default:
          printf("Internal ERROR: something wrong");
          return 0;
    }
}
