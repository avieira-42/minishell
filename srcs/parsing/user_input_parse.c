#include "parsing.h"

static
bool	is_valid_token(t_token_type previous_token, t_token_type current_token)
{
	if (previous_token == TOKEN_NULL && current_token == TOKEN_PIPE)
		return (false);
	if (is_enum_redirect_token(previous_token) == true
			&& is_enum_redirect_token(current_token) == true)
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

int	user_input_parse(char *user_input, t_token_list **tokens)
{
	/* TO CALL THE WHOLE PARSING PROCESS WITHIN THIS FUNCTION
	   AND CHECK ERRORS ALONG THE WAY */

	(void)			user_input;
	t_token_type	previous_token;
	t_token_list	*tokens_iter;

	tokens_iter = *tokens;
	previous_token = TOKEN_NULL;
	if (tokens_iter == NULL)
		return (-1);
	while (tokens_iter != NULL)
	{
		if (is_valid_token(previous_token, tokens_iter->token_type) == false)
			return (-1);
		if (tokens_iter->next == NULL)
			if (is_valid_token_final(tokens_iter->token_type) == false)
				return (-1);
		previous_token = tokens_iter->token_type;
		tokens_iter = tokens_iter->next;
	}
	return (0);
}
