#include "../minishell.h"
#include "execution.h"
#include <sys/wait.h>
#include <unistd.h>

void	pipe_execute(t_btree *node);

void	traverse_btree(t_btree *node, int is_pipe_child)
{
	if (node == NULL)
		return ;
	if (node->node_type == TOKEN_PIPE)
		pipe_execute(node);
	else
	{
		if (is_pipe_child == TRUE)
			command_execute(node->command, NULL); 
		else
		{
			if (fork() == 0)
				command_execute(node->command, NULL);
			else
				wait(0);
		}
	}
}

void	pipe_execute(t_btree *node)
{
	pipe(node->pipefd);
	if (fork() == 0)
	{
		dup2(node->pipefd[1], STDOUT_FILENO);
		safe_close(&node->pipefd[0]);
		safe_close(&node->pipefd[1]);
		traverse_btree(node->left, TRUE);
	}
	if (fork() == 0)
	{
		dup2(node->pipefd[0], STDIN_FILENO);
		safe_close(&node->pipefd[1]);
		safe_close(&node->pipefd[0]);
		traverse_btree(node->right, TRUE);
	}
	safe_close(&node->pipefd[0]);
	safe_close(&node->pipefd[1]);
}

int	command_exists(t_command *command, char **command_path)
{
	char	**path_env;
	int		exit_code;

	path_env = ft_split(getenv("PATH"), ':');
	*command_path = NULL;
	exit_code = program_path_find(command->argv[0], path_env, command_path);
	free_array((void **)path_env, -1, TRUE);
	if (exit_code == -1)
	{
		ft_printf_fd(2, ALLOC_ERROR);
		return (FALSE);
	}
	else if (exit_code == 0)
	{
		ft_printf_fd(2, NOT_FOUND_ERROR, command->argv[0]);
		return (FALSE);
	}
	else if (exit_code == 2)
	{
		ft_printf_fd(2, NO_FILE_ERROR, command->argv[0]);
		return (FALSE);
	}
	return (TRUE);
}

int	command_execute(t_command *command, char **envp)
{
	char	*command_path;
	int		pid = 0;

	if (command_exists(command, &command_path) == 0)
		return (EXIT_FAILURE);
	execve(command_path, command->argv, envp);
	perror("execve");
	free(command_path);
	return (pid);
}
