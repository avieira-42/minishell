#include "../minishell.h"

int	builtins_cd(char **argv, char **envp)
{
	char *args[] = {"ls", 0};
	(void)envp;
	if (chdir(*argv) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s\n", strerror(errno));
		return (1);
	}
	execve("/bin/ls/", args, envp);
	return (0);
}
