#include "../minishell.h"

int	builtins_exec(char **argv)
{
	if (!argv)
		return (1);
	if (*argv && ft_strcmp(argv[0], "echo") == 0)
		return (echo(&argv[1]));
	return (0);
}