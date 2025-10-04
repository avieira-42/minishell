#include "tokenizer.h"

bool    is_new_token(char *c)
{
    if (*c == PIPE || *c == REDIRECT_IN || *c == REDIRECT_OUT
        || *c == OPEN_PAREN || *c == SPACE
        || ft_bool_strncmp(c, HEREDOC, 2) == true
        || ft_bool_strncmp(c, APPEND, 2) == true
        || ft_bool_strncmp(c, LOGICAL_AND, 2) == true
        || ft_bool_strncmp(c, LOGICAL_OR, 2) == true)
        return (true);
    return (false);
}

void    tokenize_double_quoted_text(t_token_list *tokens, char *token_new, int *i) // <<< big line
{
    int     token_len;

    (*i)++;
    token_len = 0;
    while (token_new[*i] != '\0' && token_new[*i] != '\"')
    {
        (*i)++;
        token_len++;
    }
    // ITERATE ONLY IF OPERATOR HAS 2 CHARS <<<<<<<<<<<<<<<<<<
    // ITERATE ONE AT THE END
}

void    tokenize_operator(char *c, t_token_list *tokens, int *i)
{
    if (*c == SPACE)
        tokens->token_type = TOKEN_SPACE;
    else if (*c == PIPE)
        tokens->token_type = TOKEN_REDIRECT_IN; // <<<<<< create list of en
    else if (*c == REDIRECT_IN)
        (*i)++
}

void    tokenize_user_input(t_token_list *tokens, char *user_input)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(user_input[i] != '\0')
    {
        if (is_new_token(&user_input[i]) == true)
        {
            tokenize_operator(&user_input[i], tokens, &i);
            if (token->token_type == DQUOTE_LITERAL || token->token_type == SQUOTE_LITERAL)
                tokenize_double_quoted_text(tokens, c, &i);
        }
        i++;
        tokens = tokens->next;
    }
}
