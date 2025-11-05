#include "builtins.h"

void	builtins_export_printf(t_shell *shell)
{
	size_t	i;

	i = 0;
	while (shell->export_vars[i] != NULL)
	{
		ft_printf("declare -x %s
	}
}

void	builtins_export(t_shell *shell, char **argv)
{
	if (argv[0] != NULL && argv[1] == NULL)
	{
		builtins_export_print(shell)
	}
}
