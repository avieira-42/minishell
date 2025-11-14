#include "parsing.h"
#include "../types.h"
#include "../cleaning/cleaning.h"

bool    is_operator(char *c)
{
    if (ft_bool_strncmp(c, HEREDOC, 2) == true
        || ft_bool_strncmp(c, APPEND, 2) == true
        || *c == PIPE || *c == REDIRECT_IN
        || *c == REDIRECT_OUT || ft_isspace(*c))
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

void
tokenize_operator(t_shell *shell, char *c, t_token_list **tokens, int *i)
{
	(void)shell;
    t_token_list    *token_node_new;

    if (*c == SPACE)
    {
        (*i)++;
        return ;
    }
    token_node_new = ft_token_lst_new(NULL);
	if (token_node_new == NULL)
		exit_clean(shell, 1, NULL);
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
		exit_clean(shell, 1, NULL);
    (*i)++;
}

void    tokenize_word(t_shell *shell, int i, int j)
{
    char            *token_new;
    t_token_list    *token_node_new;

    if (i == j)
        return ;
    token_new = ft_substr(shell->user_input, j, i - j);
	if (token_new == NULL)
		exit_clean(shell, 1, NULL);
    token_node_new = ft_token_lst_new(token_new);
	if (token_node_new == NULL)
	{
		free(token_new);
		exit_clean(shell, 1, NULL);
	}
    ft_token_lst_add_back(&shell->tokens, token_node_new);
}

void    tokenize_user_input(t_shell *shell)
{
    int             i;
    int             j;

    i = 0;
    j = 0;
    while(shell->user_input[i] != '\0')
    {
        tokenize_quoted_text(&shell->tokens, shell->user_input, &i);
        if (is_operator(&shell->user_input[i]) == true)
        {
            tokenize_word(shell,i, j);
            tokenize_operator(shell, &shell->user_input[i], &shell->tokens, &i);
            j = i;
        }
        else if (shell->user_input[i] != '\0')
            i++;
    }
    if (i > j)
		tokenize_word(shell, i, j);
	free(shell->user_input);
	shell->user_input = NULL;
}
