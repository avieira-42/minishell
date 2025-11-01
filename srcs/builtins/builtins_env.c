#include "../minishell.h"
#include <stdlib.h>

int	builtins_env(char **argv, char **envp)
{
	if (envp == NULL)
	{
		ft_putendl_fd("minishell: env: no envp provided", 2);
		return (EXIT_FAILURE);
	}
	if (*argv != NULL)
	{
		ft_putendl_fd("minishell: env: too many arguments", 2);
		return (EXIT_FAILURE);
	}
	while (*envp != NULL)
		ft_putendl_fd(*envp++, 1);
	return (EXIT_SUCCESS);
}
