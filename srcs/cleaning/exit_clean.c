#include "../types.h"
#include "cleaning.h"
#include "../parsing/parsing.h"
#include "../binary_tree/binary_tree.h"

void	exit_clean(t_shell *shell, int exit_code)
{
	if (shell->user_input != NULL)
		free(shell->user_input);
	if (shell->tokens != NULL)
		ft_token_lst_clear(&shell->tokens);
	if (shell->tree != NULL)
		btree_clear(&shell->tree);
	if (shell->env_vars != NULL)
		free_array((void *)shell->env_vars, -1, true);
	if (shell->export_vars.m_array != NULL)
		free_array((void *)shell->export_vars.m_array, -1, true);
	exit (exit_code);
}
