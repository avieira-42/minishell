#include "../minishell.h"
#include "execution.h"

void	pipe_parent(int fd[2], int *exit_code, int pid_left, int pid_right)
{
	safe_close(&fd[0]);
	safe_close(&fd[1]);
	waitpid(pid_left, exit_code, 0);
	waitpid(pid_right, exit_code, 0);
	if (WIFEXITED(*exit_code))
		*exit_code = WEXITSTATUS(*exit_code);
}

int	pipe_child(t_pipe_args *args)
{
	int	pid;
	int	exit_status;

	pid = safe_fork(args->shell);
	if (pid == 0)
	{
		signal(SIGPIPE, signal_broken_pipe);
		safe_dup2(args->oldfd, args->newfd, args->shell);
		close(args->fd[0]);
		close(args->fd[1]);
		exit_status = traverse_btree(args->node, args->shell);
		exit_clean(args->shell, exit_status, NULL, NULL);
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

void	stdfd_restore(int fd[2], t_shell *shell)
{
	safe_dup2(fd[0], STDIN_FILENO, shell);
	safe_dup2(fd[1], STDOUT_FILENO, shell);
	close(fd[0]);
	close(fd[1]);
}
