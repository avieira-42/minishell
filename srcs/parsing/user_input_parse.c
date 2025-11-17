#include "parsing.h"
#include "../binary_tree/binary_tree.h"

static
bool	is_valid_token(t_token_type previous_token, t_token_type current_token)
{
	if (previous_token == TOKEN_NULL && current_token == TOKEN_PIPE)
		return (false);
	if (is_enum_redirect_token(previous_token) == true
		&& is_enum_redirect_token(current_token) == true)
		return (false);
	if (is_enum_redirect_token(previous_token) == true
		&& current_token == TOKEN_PIPE)
		return (false);
	if (previous_token == TOKEN_PIPE && current_token == TOKEN_PIPE)
		return (false);
	return (true);
}

static
bool	is_valid_token_final(t_token_type final_token)
{
	if (final_token == TOKEN_PIPE)
		return (false);
	if (is_enum_redirect_token(final_token))
		return (false);
	return (true);
}

int	user_input_parse(t_shell *shell)
{
	t_token_type	previous_token;
	t_token_list	*tokens_iter;

	tokenize_user_input(shell);
	token_identify(shell->tokens);
	quotation_check(shell->tokens);
	token_expand(shell);
	quote_removal(shell->tokens);
	tokens_iter = shell->tokens;
	previous_token = TOKEN_NULL;
	while (tokens_iter != NULL)
	{
		if (is_valid_token(previous_token, tokens_iter->token_type) == false)
			return (ft_printf_fd(2, "minishell: Error: Invalid input\n"), -1);
		if (tokens_iter->is_open_quoted == true)
			return (ft_printf_fd(2, "minishell: Error: Invalid input\n"), -1);
		if (tokens_iter->next == NULL)
			if (is_valid_token_final(tokens_iter->token_type) == false)
				return (ft_printf_fd(2, INPUT_ERR), -1);
		previous_token = tokens_iter->token_type;
		tokens_iter = tokens_iter->next;
	}
	btree_create(shell);
	return (0);
}
