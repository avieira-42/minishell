#include "parsing.h"

void	error_exit_tokens(char *user_input, t_token_list *tokens, int error_code)
{
	char	*error_message;

	if (user_input != NULL)
		free(user_input);
	if (tokens != NULL)
		ft_token_lst_clear(&tokens);
	error_message_get(error_code, &error_message);
	error_message_put_tokens(error_message);
	exit (error_code);
}
