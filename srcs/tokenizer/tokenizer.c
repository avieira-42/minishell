#include "tokenizer.h"

bool    is_new_token(char *c)
{
    if (*c == SPACE || *c == PIPE || *c == REDIRECT_IN || *c == REDIRECT_OUT
        || ft_bool_strncmp(c, HEREDOC, 2) == true
        || ft_bool_strncmp(c, APPEND, 2) == true
        || ft_bool_strncmp(c, LOGICAL_AND, 2) == true
        || ft_bool_strncmp(c, LOGICAL_OR, 2) == true)
        return (true);
    return (false);
}

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

void    tokenize_operator(char *c, t_list *tokens, int *i)
{
    if (*c == SPACE)
        (*i)++;
    else if (*c == PIPE)
        tokens->content = TOKEN_REDIRECT_IN; // <<<<<< create list of enum
}

void    tokenize_user_input(t_list *tokens, char *user_input)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(user_input[i] != '\0')
    {
        if (user_input[i] == '\"')
            tokenize_double_quoted_text(tokens, &user_input[i], &i);
        if (is_new_token(&user_input[i]) == true)
            tokenize_operator(&user_input[i], tokens, &i);
        i++;
        tokens = tokens->next;
    }
}
