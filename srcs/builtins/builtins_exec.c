#include "../minishell.h"

int	builtins_exec(char **argv)
{
	if (!argv)
		return (1);
	if (*argv && ft_strcmp(argv[0], "echo") == 0)
		return (builtins_echo(&argv[1]));
	else if (*argv && ft_strcmp(argv[0], "pwd") == 0)
		return (builtins_pwd());
	return (0);
}
