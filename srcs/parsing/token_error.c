#include "parsing.h"

void	error_exit_tokens(char *user_input, t_token_list *toks, int error_code)
{
	char	*error_message;

	if (user_input != NULL)
		free(user_input);
	if (toks != NULL)
		ft_token_lst_clear(&toks);
	error_message_get(error_code, &error_message);
	error_message_put_tokens(error_message);
	exit (error_code);
}
