#include "../minishell.h"

int	builtins_env(char **envp)
{
	while (*envp != NULL)
		ft_putendl_fd(*envp++, 1);
	return (EXIT_SUCCESS);
}
