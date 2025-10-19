#include "tokenizer.h"

bool    is_pipe(t_token_list *token)
{
    if (token->token_string[0] == PIPE) return (true);
    return (false);
}

bool    is_enum_redirect_token(t_token_type token)
{
    if (token >= 1 && token <= 4)
        return (true);
    return (false);
}

bool    is_redirect(t_token_list *token)
{
    if (ft_bool_strncmp(token->token_string, HEREDOC, 2) == true
        || ft_bool_strncmp(token->token_string, APPEND, 2) == true
        || token->token_string[0] == REDIRECT_IN
        || token->token_string[0] == REDIRECT_OUT)
        return (true);
    return (false);
}

bool    token_redirect_identify(t_token_list *token)
{
    if (ft_bool_strncmp(token->token_string, HEREDOC, 2) == true)
        token->token_type = TOKEN_HEREDOC;
    if (ft_bool_strncmp(token->token_string, APPEND, 2) == true)
        token->token_type = TOKEN_APPEND;
    if (token->token_string[0] == REDIRECT_IN)
        token->token_type = TOKEN_REDIRECT_IN;
    if (token->token_string[0] == REDIRECT_OUT)
        token->token_type = TOKEN_REDIRECT_OUT;
    return (false);
}

void    token_identify(t_token_list *tokens)
{
    t_token_type    previous_token;

    previous_token = TOKEN_NULL;
    while (tokens != NULL)
    {
        if (is_pipe(tokens) == true)
            tokens->token_type = TOKEN_PIPE;
        else if (is_redirect(tokens) == true)
            token_redirect_identify(tokens);
        else if (previous_token == TOKEN_PIPE)
            tokens->token_type = TOKEN_CMD;
        else if (is_enum_redirect_token(previous_token) == true)
            tokens->token_type = TOKEN_FILE;
        else if (previous_token == TOKEN_NULL)
            tokens->token_type = TOKEN_CMD;
        previous_token = tokens->token_type;
        tokens = tokens->next;
    }
}
