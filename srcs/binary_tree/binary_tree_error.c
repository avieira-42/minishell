#include "binary_tree.h"

void	error_exit_btree(t_btree *btree, t_token_list *tokens, int error_code)
{
	char	*error_message;

	if (tokens != NULL)
		ft_token_lst_clear(&tokens);
	if (btree != NULL)
	   btree_clear(btree);
	error_message_get(error_code, &error_message);
	error_message_put_tokens(error_message);
	exit (error_code);
}
