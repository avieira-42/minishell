#include "../binary_tree/binary_tree.h"

void	iteration_clear(t_shell *shell)
{
	if (shell->tree != NULL)
		btree_clear(&shell->tree);
	if (shell->tokens != NULL)
		ft_token_lst_clear(&shell->tokens);
	str_merge_sort(shell->export_vars, &shell->merge_ret);
	if (shell->merge_ret == -1)
		return ; // SAFE EXIT
}
