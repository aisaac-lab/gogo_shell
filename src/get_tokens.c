#include <stdio.h>
#include <string.h>
#include "get_tokens.h"

int
get_tokens(char *str, char tokens[MAX_NUM_OF_TOKEN][MAX_LEN_OF_TOKEN], int token_nums[MAX_NUM_OF_TOKEN]) {
    int len_of_str = strlen(str);
    int count_of_tokens = 0;
    for (int i=0; i<len_of_str; i++) {
        char token[MAX_LEN_OF_TOKEN] = "";
        int token_num = TKN_SPC;

        if (is_special_char(str[i])) {
            token_num = token_num_of_special_char(str[i]);
            token[0] = str[i];
        } else if (is_space(str[i])) {
        } else  {
            int current_i = i;
            for (; i<len_of_str && !is_special_char(str[i]); i++){
                token[i-current_i] = str[i];
            }
            i--;
            token_num = TKN_NORMAL;
        }

        if (token_num != TKN_SPC) {
            for(int k=0; token[k]; k++) {
                tokens[count_of_tokens][k] = token[k];
            }
            token_nums[count_of_tokens] = token_num;
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
