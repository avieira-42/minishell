#include "builtins.h"

void	builtins_unset_from_matrix(t_shell *shell, char *variable)
{
	int	i;

	i = 0;
	while (shell->env_vars[i] != NULL)
	{
		if (shell->env_vars[i] == variable)
		{
		}
		i++;
	}
}

int	builtin_unset(t_shell *shell, char *variables)
{
	builtins_unset_from_vars();
	builtins_unset_from_env();
	return (0);
}
