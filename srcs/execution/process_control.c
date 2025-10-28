#include "../minishell.h"

void	pipe_parent(int fd[2], int *exit_code, int pid_left, int pid_right)
{
	safe_close(&fd[0]);
	safe_close(&fd[1]);
	waitpid(pid_left, exit_code, 0);
	waitpid(pid_right, exit_code, 0);
	if (WIFEXITED(*exit_code))
		*exit_code = WEXITSTATUS(*exit_code);
}

int	pipe_child(int fd[2], t_btree *node, int oldfd, int newfd)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(oldfd, newfd);
		safe_close(&fd[1]);
		safe_close(&fd[0]);
		traverse_btree(node);
	}
	return (pid);
}
