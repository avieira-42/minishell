#include "../minishell.h"

int	builtins_exec(char **argv, char **envp)
{
	if (argv == NULL)
		return (-1);
	if (*argv != NULL && ft_strcmp(argv[0], "echo") == 0)
		return(builtins_echo(&argv[1]));
	else if (*argv != NULL && ft_strcmp(argv[0], "pwd") == 0)
		return(builtins_pwd());
	else if (*argv != NULL && ft_strcmp(argv[0], "cd") == 0)
		return(builtins_cd(&argv[1], envp));
	else
		return (-1);
}
