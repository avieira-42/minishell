#include "../minishell.h"
#include "execution.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static
int	command_exists(t_command *command, char **command_path)
{
	char	**path_env;
	int		exit_code;

	path_env = ft_split(getenv("PATH"), ':');
	*command_path = NULL;
	exit_code = program_path_find(command->argv[0], path_env, command_path);
	free_array((void **)path_env, -1, TRUE);
	if (exit_code == ALLOC_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, ALLOC_ERROR);
		return(EXIT_FAILURE);
	}
	else if (exit_code == NOT_FOUND_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NOT_FOUND_ERROR, command->argv[0]);
		return(EXIT_NOT_FOUND);
	}
	else if (exit_code == NO_FILE_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NO_FILE_ERROR, command->argv[0]);
		return(EXIT_NOT_FOUND);
	}
	return (EXIT_SUCCESS);
}

static
void	pipe_execute(t_btree *node, int *exit_code, t_btree *head)
{
	int	pipefd[2];
	int	pid_left;
	int	pid_right;

	safe_pipe(pipefd);
	pid_left = pipe_child(pipefd, node->left, pipefd[1], STDOUT_FILENO, head);
	pid_right = pipe_child(pipefd, node->right, pipefd[0], STDIN_FILENO, head);
	pipe_parent(pipefd, exit_code, pid_left, pid_right);
}

static
int	redirect_execute(t_btree *node)
{
	char		*filename;
	int			fd;
	int			open_flags;
	t_redirect	*tmp;

	filename = node->command->redirects->filename;
	fd = node->command->redirects->fd;
	open_flags = node->command->redirects->open_flags;
	if (node->command->redirects->redir_type != TOKEN_HEREDOC)
	{
		safe_close(&fd);
		if (open(filename, open_flags, 0644) < 0)
		{
			ft_printf_fd(
				STDERR_FILENO, "%s: %s\n",
				filename, strerror(errno));
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		safe_dup2(fd, STDIN_FILENO);
		safe_close(&fd);
	}
	tmp = node->command->redirects->next;
	free(node->command->redirects->filename);
	free(node->command->redirects);
	node->command->redirects = tmp;
	return (traverse_btree(node));
}

static
int	command_execute(t_command *command, char **envp)
{
	char	*command_path;
	int		exit_status;
	int		pid;

	exit_status = builtins_exec(command->argv, envp);
	if (exit_status != -1)
		return (exit_status);
	exit_status = command_exists(command, &command_path);
	if (exit_status != EXIT_SUCCESS)
		return (exit_status);
	pid = safe_fork();
	if (pid == 0)
	{
		execve(command_path, command->argv, envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &exit_status, 0);
	free(command_path);
	exit_status = WEXITSTATUS(exit_status);
	return(exit_status);
}

int	traverse_btree(t_btree *node)
{
	t_btree	*test;
	int	exit_status;

	test = node;
	exit_status = 0;
	if (node == NULL)
		exit(exit_status);
	if (node->node_type != TOKEN_PIPE && node->command->redirects != NULL)
		return (redirect_execute(node));
	if (node->node_type == TOKEN_PIPE)
		pipe_execute(node, &exit_status, test);
	else
		exit_status = command_execute(node->command, NULL);
	return(exit_status);
}
