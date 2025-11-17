#include "parsing.h"

void	token_expand(t_shell *sh)
{
	t_token_list	*tokens;

	tokens = sh->tokens;
	while (tokens != NULL)
	{
		token_expansion_create(&tokens->token_string, sh);
		tokens = tokens->next;
	}
}
