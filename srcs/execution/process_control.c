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

	pid = safe_fork();
	if (pid == 0)
	{
		safe_dup2(oldfd, newfd);
		safe_close(&fd[1]);
		safe_close(&fd[0]);
		traverse_btree(node);
		exit(0);
	}
	return (pid);
}

int	*stdfd_save(void)
{
	static int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	return (fd);
}

void	stdfd_restore(int fd[2])
{
	safe_dup2(STDIN_FILENO, fd[0]);
	safe_dup2(STDOUT_FILENO, fd[1]);
}
