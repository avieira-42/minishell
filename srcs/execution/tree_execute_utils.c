#include <sys/types.h>
#include <sys/stat.h>
#include "../minishell.h"

int	redirect_open(int *fd, int open_flags, char *filename)
{
	safe_close(fd);
	if (open(filename, open_flags, 0644) < 0)
	{
		ft_printf_fd(
			STDERR_FILENO, "%s: %s\n",
			filename, strerror(errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	heredoc_open(int *ptr_fd)
{
	safe_dup2(*ptr_fd, STDIN_FILENO);
	safe_close(ptr_fd);
}

int	ft_wait(int pid)
{
	int	exit_code;

	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(exit_code) == TRUE)
		return (WEXITSTATUS(exit_code));
	else if (WIFSIGNALED(exit_code) == TRUE)
		exit_code = WTERMSIG(exit_code) + 128;
	if (exit_code == 131)
		ft_printf_fd(2, "quit (core dumped)\n");
	else if (exit_code == 130)
		ft_printf_fd(2, "\n");
	return (exit_code);
}

int	is_directory(char *cmd_name)
{
	struct stat	status;

	status = (struct stat){};
	lstat(cmd_name, &status);
	if ((status.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_printf_fd(STDERR_FILENO, DIR_ERR, cmd_name);
		return (TRUE);
	}
	return (FALSE);
}
