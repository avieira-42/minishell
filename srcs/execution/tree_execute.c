/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:49:58 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:49:59 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "../cleaning/cleaning.h"
#include "execution.h"

static
void	pipe_execute(t_btree *node, int *exit_code, t_shell *shell)
{
	int			pipefd[2];
	int			pid_left;
	int			pid_right;
	t_pipe_args	left_node;
	t_pipe_args	right_node;

	safe_pipe(pipefd, shell);
	left_node.node = node->left;
	left_node.shell = shell;
	left_node.fd = pipefd;
	left_node.oldfd = pipefd[1];
	left_node.newfd = STDOUT_FILENO;
	right_node.node = node->right;
	right_node.shell = shell;
	right_node.fd = pipefd;
	right_node.oldfd = pipefd[0];
	right_node.newfd = STDIN_FILENO;
	pid_left = pipe_child(&left_node);
	pid_right = pipe_child(&right_node);
	pipe_parent(pipefd, exit_code, pid_left, pid_right);
}

static
int	redirect_execute(t_btree *node, t_shell *shell)
{
	char		*filename;
	int			*fd;
	int			open_flags;
	t_redirect	*tmp;

	filename = node->command->redirects->filename;
	fd = &node->command->redirects->fd;
	open_flags = node->command->redirects->open_flags;
	if (node->command->redirects->redir_type != TOKEN_HEREDOC)
	{
		if (redirect_open(fd, open_flags, filename) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else
		heredoc_open(fd, shell);
	tmp = node->command->redirects->next;
	free(node->command->redirects->filename);
	free(node->command->redirects);
	node->command->redirects = tmp;
	return (traverse_btree(node, shell));
}

static
void	command_execute_free_path(t_command *command, char *command_path)
{
	if (command->argv[0] != command_path)
		free(command_path);
}

static
int	command_execute(t_command *command, char **envp, t_shell *shell)
{
	char	*command_path;
	int		exit_status;
	int		pid;

	if (command->argv[0] == NULL)
		return (EXIT_SUCCESS);
	exit_status = builtins_exec(command->argv, envp, shell);
	if (exit_status != -1)
		return (exit_status);
	if (is_directory(command->argv[0], FALSE, TRUE) == TRUE)
		return (126);
	exit_status = command_exists(command, &command_path, envp);
	if (exit_status != EXIT_SUCCESS)
		return (exit_status);
	pid = safe_fork(shell);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		close_all_fds(3, shell->highest_fd);
		execve(command_path, command->argv, envp);
		exit_clean(shell, 2, NULL, NULL);
	}
	command_execute_free_path(command, command_path);
	return (ft_wait(pid));
}

int	traverse_btree(t_btree *node, t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	if (node == NULL)
		exit_clean(shell, EXIT_FAILURE, NULL, NULL);
	if (node->node_type != TOKEN_PIPE && node->command->redirects != NULL)
		return (redirect_execute(node, shell));
	if (node->node_type == TOKEN_PIPE)
		pipe_execute(node, &exit_status, shell);
	else
		exit_status = command_execute(node->command, shell->env_vars, shell);
	return (exit_status);
}
