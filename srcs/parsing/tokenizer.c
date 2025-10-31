#include "parsing.h"

bool    is_operator(char *c)
{
    if (ft_bool_strncmp(c, HEREDOC, 2) == true
        || ft_bool_strncmp(c, APPEND, 2) == true
        || *c == PIPE || *c == REDIRECT_IN
        || *c == REDIRECT_OUT || *c == SPACE)
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

void    tokenize_quoted_text(t_token_list **tokens, char *user_input, int *i/*, int j*/)
{
    if ((user_input[*i] != DQUOTE_LITERAL && user_input[*i] != SQUOTE_LITERAL)
        || user_input[*i] == '\0')
        return ;
    if (user_input[*i] == DQUOTE_LITERAL)
        tokenize_dquoted_text(tokens, user_input, i);
    else if (user_input[*i] == SQUOTE_LITERAL)
        tokenize_squoted_text(tokens, user_input, i);
}

int    tokenize_operator(char *c, t_token_list **tokens, int *i)
{
    t_token_list    *token_node_new;

    if (*c == SPACE)
    {
        (*i)++;
        return (0);
    }
    token_node_new = ft_token_lst_new(NULL);
	if (token_node_new == NULL)
		return (-1);
    ft_token_lst_add_back(tokens, token_node_new);
	if (ft_bool_strncmp(c, HEREDOC, 2) == true)
		(token_node_new->token_string = ft_strdup(HEREDOC), (*i)++);
	else if (ft_bool_strncmp(c, APPEND, 2) == true)
		(token_node_new->token_string = ft_strdup(APPEND), (*i)++);
	else if (*c == PIPE)
		token_node_new->token_string = ft_strdup(STRING_PIPE);
	else if (*c == REDIRECT_IN)
		token_node_new->token_string = ft_strdup(STRING_REDIRECT_IN);
	else if (*c == REDIRECT_OUT)
		token_node_new->token_string = ft_strdup(STRING_REDIRECT_OUT);
	if (token_node_new->token_string == NULL)
		return (-1);
    (*i)++;
	return (0);
}

int    tokenize_word(t_token_list **tokens, char *user_input, int i, int j)
{
    char            *token_new;
    t_token_list    *token_node_new;

    if (i == j)
        return (0);
    token_new = ft_substr(user_input, j, i - j);
	if (token_new == NULL)
		return (-1);
    token_node_new = ft_token_lst_new(token_new);
	if (token_node_new == NULL)
		return (-1);
    ft_token_lst_add_back(tokens, token_node_new);
	return (0);
}

void    tokenize_user_input(t_token_list **tokens, char *user_input)
{
    int             i;
    int             j;

    i =0;
    j = 0;
    while(user_input[i] != '\0')
    {
        tokenize_quoted_text(tokens, user_input, &i);
        if (is_operator(&user_input[i]) == true)
        {
            if (tokenize_word(tokens, user_input, i, j) == -1)
				error_exit_tokens(user_input, *tokens, 1);
            if (tokenize_operator(&user_input[i], tokens, &i) == -1)
				error_exit_tokens(user_input, *tokens, 1);
            j = i;
        }
        else
            i++;
    }
    if (i > j)
        tokenize_word(tokens, user_input, i, j);
	// free(*user_input);
	// *user_input == NULL;
}
