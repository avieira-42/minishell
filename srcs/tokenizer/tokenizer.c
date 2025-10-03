#include "tokenizer.h"

void    tokenize_double_quoted_text(t_list *tokens, char *token_new, int *i)
{
    int     token_len;

    (*i)++;
    token_len = 0;
    while (token_new[*i] != '\0' && token_new[*i] != '\"')
    {
        (*i)++;
        token_len++;
    }
}

void    tokenize_input(t_list *tokens, char *input)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(input[i] != '\0')
    {
        if (input[i] == '\"')
            tokenize_double_quoted_text(tokens, &input[i], &i);
    }
}

