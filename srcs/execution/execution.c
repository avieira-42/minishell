/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:49:18 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:49:30 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../types.h"
#include "../execution/execution.h"
#include "../cleaning/cleaning.h"

int	handle_heredoc(t_shell *shell)
{
	int	stdin_save;

	stdin_save = dup(STDIN_FILENO);
	heredoc_find(shell->tree, shell);
	safe_dup2(stdin_save, STDIN_FILENO, shell);
	if (g_last_signal == 130)
	{
		shell->exit_code = g_last_signal;
		iteration_clear(shell);
		g_last_signal = -1;
		return (0);
	}
	return (1);
}

void	tree_execute(t_shell *shell)
{
	shell->stdfd = stdfd_save();
	update_highest_fd_array(shell, shell->stdfd);
	shell->exit_code = traverse_btree(shell->tree, shell);
	stdfd_restore(shell->stdfd, shell);
}
