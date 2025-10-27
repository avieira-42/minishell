#include "../minishell.h"
#include "execution.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static
void	parent_process(int pipefd[2], int *exit_code, int pid_left, int pid_right)
{
	safe_close(&pipefd[0]);
	safe_close(&pipefd[1]);
	waitpid(pid_left, exit_code, 0);
	waitpid(pid_right, exit_code, 0);
	if (WIFEXITED(*exit_code))
		*exit_code = WEXITSTATUS(*exit_code);
}

static
void	pipe_execute(t_btree *node, int *exit_code)
{
	int	pipefd[2];
	int	pid_left;
	int	pid_right;

	pipe(pipefd);
	pid_left = fork();
	if (pid_left == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		safe_close(&pipefd[0]);
		safe_close(&pipefd[1]);
		traverse_btree(node->left);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		safe_close(&pipefd[1]);
		safe_close(&pipefd[0]);
		traverse_btree(node->right);
	}
	parent_process(pipefd, exit_code, pid_left, pid_right);
}

static
void	command_exists(t_command *command, char **command_path)
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
		exit(EXIT_FAILURE);
	}
	else if (exit_code == NOT_FOUND_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NOT_FOUND_ERROR, command->argv[0]);
		exit(EXIT_NOT_FOUND);
	}
	else if (exit_code == NO_FILE_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NO_FILE_ERROR, command->argv[0]);
		exit(EXIT_NOT_FOUND);
	}
}

static
int	command_execute(t_command *command, char **envp)
{
	char	*command_path;

	command_exists(command, &command_path);
	execve(command_path, command->argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	traverse_btree(t_btree *node)
{
	int	exit_status;

	exit_status = 0;
	if (node == NULL)
		return ;
	if (node->node_type == TOKEN_PIPE)
		pipe_execute(node, &exit_status);
	else
		command_execute(node->command, NULL);
	exit(exit_status);
}

