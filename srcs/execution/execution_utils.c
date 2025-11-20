/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:49:27 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:49:32 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdlib.h>

int	safe_fork(t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit_clean(shell, 2, NULL, NULL);
	}
	return (pid);
}

void	safe_dup2(int oldfd, int newfd, t_shell *shell)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2");
		exit_clean(shell, 2, NULL, NULL);
	}
}

void	safe_pipe(int pipefd[2], t_shell *shell)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit_clean(shell, 2, NULL, NULL);
	}
	update_highest_fd_array(shell, pipefd);
}

void	update_highest_fd(t_shell *shell, int fd)
{
	if (shell->highest_fd < fd)
		shell->highest_fd = fd;
}

void	update_highest_fd_array(t_shell *shell, int *fd_array)
{
	update_highest_fd(shell, fd_array[0]);
	update_highest_fd(shell, fd_array[1]);
}
