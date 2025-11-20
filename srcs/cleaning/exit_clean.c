#include "../types.h"
#include "cleaning.h"
#include "../parsing/parsing.h"
#include "../binary_tree/binary_tree.h"

void	exit_clean(t_shell *shell, int exit_code, char **array, char *string)
{
	if (string != NULL)
		free(string);
	if (array != NULL)
		free_array((void *)array, -1, true);
	if (shell->user_input != NULL)
		free(shell->user_input);
	if (shell->tokens != NULL)
	{
		ft_token_lst_clear(&shell->tokens);
		btree_clear_safe(&shell->tree);
	}
	else if (shell->tree != NULL)
		btree_clear(&shell->tree);
	if (shell->env_vars != NULL)
		free_array((void *)shell->env_vars, -1, true);
	if (shell->export_vars.m_array != NULL)
		free_array((void *)shell->export_vars.m_array, -1, true);
	if (exit_code == 1)
		ft_printf_fd(2, "minishell: Error: Could not allocate memory\n");
	close_all_fds(3, shell->highest_fd);
	exit(exit_code);
}
