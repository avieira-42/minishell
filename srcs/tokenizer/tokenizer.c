#include "tokenizer.h"

bool    is_operator(char *c)
{
    if (ft_bool_strncmp(c, HEREDOC, 2) == true
        || ft_bool_strncmp(c, APPEND, 2) == true
        || *c == PIPE || *c == REDIRECT_IN
        || *c == REDIRECT_OUT || *c == SPACE
        /*|| ft_bool_strncmp(c, LOGICAL_AND, 2) == true
        || ft_bool_strncmp(c, LOGICAL_OR, 2) == true)*/)
    {

        return (true);
    }
    return (false);
}

void    tokenize_dquoted_text(t_token_list **tokens, char *user_input, int *i)
{
    (*i)++;
    while (user_input[*i] != '\0' && user_input[*i] != DQUOTE_LITERAL)
        (*i)++;
    if (user_input[*i] != '\0')
        (*i)++;
    if (user_input[*i] == DQUOTE_LITERAL)
        tokenize_dquoted_text(tokens, user_input, i);
    else if (user_input[*i] == SQUOTE_LITERAL)
        tokenize_squoted_text(tokens, user_input, i);
}

void    tokenize_squoted_text(t_token_list **tokens, char *user_input, int *i)
{
    (*i)++;
    while (user_input[*i] != '\0' && user_input[*i] != SQUOTE_LITERAL)
        (*i)++;
    if (user_input[*i] != '\0')
        (*i)++;
    if (user_input[*i] == DQUOTE_LITERAL)
        tokenize_dquoted_text(tokens, user_input, i);
    else if (user_input[*i] == SQUOTE_LITERAL)
        tokenize_squoted_text(tokens, user_input, i);
}

void    tokenize_quoted_text(t_token_list **tokens, char *user_input, int *i, int j)
{
    char            *token_new;
    t_token_list    *token_node_new;
 
    if (user_input[*i] != DQUOTE_LITERAL && user_input[*i] != SQUOTE_LITERAL)
        return ;
    if (user_input[*i] == DQUOTE_LITERAL)
        tokenize_dquoted_text(tokens, user_input, i);
    else if (user_input[*i] == SQUOTE_LITERAL)
        tokenize_squoted_text(tokens, user_input, i);
    token_new = ft_substr(user_input, j, *i - j);
    token_node_new = ft_token_lst_new(token_new);
    if (user_input[(*i) - 1] != DQUOTE_LITERAL
        && user_input[(*i) - 1] != SQUOTE_LITERAL) 
        token_node_new->is_open_quoted = true;
    else
        token_node_new->is_quoted = true;
    ft_token_lst_add_back(tokens, token_node_new);
}

void    tokenize_operator(char *c, t_token_list **tokens, int *i)
{
    /* CREATE TOKENIZE_SINGLE_CHAR_OPERATOR and TOKENIZE_DOUBLE_CHAR_OPERATOR and TOKENIZE_SPACE_OPERATOR
       WITH iteration on double char operator and free on space*/
    t_token_list    *token_node_new;

    if (*c == SPACE)
    {
        (*i)++;
        return ;
    }
    token_node_new = ft_token_lst_new(NULL);
    ft_token_lst_add_back(tokens, token_node_new);
    if (ft_bool_strncmp(c, HEREDOC, 2) == true)
        (token_node_new->token_string = ft_strdup(HEREDOC), (*i)++);
    else if (ft_bool_strncmp(c, APPEND, 2) == true)
        (token_node_new->token_string = ft_strdup(HEREDOC), (*i)++);
    else if (*c == PIPE)
        token_node_new->token_string = ft_strdup(STRING_PIPE);
    else if (*c == REDIRECT_IN)
        token_node_new->token_string = ft_strdup(STRING_REDIRECT_IN);
    else if (*c == REDIRECT_OUT)
        token_node_new->token_string = ft_strdup(STRING_REDIRECT_OUT);
    /*else if (ft_bool_strncmp(c, LOGICAL_AND, 2) == true)
      (token_node_new->token_type = TOKEN_HEREDOC, (*i)++);
      else if (ft_bool_strncmp(c, LOGICAL_OR, 2) == true)
      (token_node_new->token_type = TOKEN_LOGICAL_OR, (*i)++);
      else if (ft_bool_strncmp(c, LOGICAL_AND, 2) == true)
      (token_node_new->token_type = TOKEN_LOGICAL_AND, (*i)++);*/
    (*i)++;
}

void    tokenize_word(t_token_list **tokens, char *user_input, int i, int j)
{
    char            *token_new;
    t_token_list    *token_node_new;

    if (i == j)
        return ;
    token_new = ft_substr(user_input, j, i - j);
    token_node_new = ft_token_lst_new(token_new);
    ft_token_lst_add_back(tokens, token_node_new);
}

void    tokenize_user_input(t_token_list **tokens, char *user_input)
{
    int             i;
    int             j;

    i =0;
    j = 0;
    while(user_input[i] != '\0')
    {
        if (user_input[i] == SQUOTE_LITERAL || user_input[i] ==DQUOTE_LITERAL)
        {
            tokenize_quoted_text(tokens, user_input, &i, j);
            j = i;
        }
        else if (is_operator(&user_input[i]) == true)
        {
            tokenize_word(tokens, user_input, i, j);
            tokenize_operator(&user_input[i], tokens, &i);
            tokenize_quoted_text(tokens, user_input, &i, i);
            j = i;
        }
        else
            i++;
    }
    if (i > j)
        tokenize_word(tokens, user_input, i, j);
}
