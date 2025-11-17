#include "parsing.h"
#include "../types.h"
#include "../cleaning/cleaning.h"

bool	is_operator(char *c)
{
	if (ft_bool_strncmp(c, HEREDOC, 2) == true
		|| ft_bool_strncmp(c, APPEND, 2) == true
		|| *c == PIPE || *c == REDIRECT_IN
		|| *c == REDIRECT_OUT || ft_isspace(*c))
		return (true);
	return (false);
}

void	tokenize_quoted_text(t_token_list **tokens, char *user_input, int *i)
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
	t_token_list	*token_node_new;

	if (*c == SPACE)
	{
		(*i)++;
		return ;
	}
	token_node_new = ft_token_lst_new(NULL);
	if (token_node_new == NULL)
		exit_clean(shell, 1, NULL, NULL);
	ft_token_lst_add_back(tokens, token_node_new);
	tokenize_operator_set(token_node_new, c, i);
	if (token_node_new->token_string == NULL)
		exit_clean(shell, 1, NULL, NULL);
	(*i)++;
}

void	tokenize_word(t_shell *shell, int i, int j)
{
	char			*token_new;
	t_token_list	*token_node_new;

	if (i == j)
		return ;
	token_new = ft_substr(shell->user_input, j, i - j);
	if (token_new == NULL)
		exit_clean(shell, 1, NULL, NULL);
	token_node_new = ft_token_lst_new(token_new);
	if (token_node_new == NULL)
	{
		free(token_new);
		exit_clean(shell, 1, NULL, NULL);
	}
	ft_token_lst_add_back(&shell->tokens, token_node_new);
}

void	tokenize_user_input(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (shell->user_input[i] != '\0')
	{
		tokenize_quoted_text(&shell->tokens, shell->user_input, &i);
		if (is_operator(&shell->user_input[i]) == true)
		{
			tokenize_word(shell, i, j);
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
