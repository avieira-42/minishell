#include "builtins.h"

static	inline
void	builtins_export_printvar(char **var_value)
{
	while (**var_value != '\0')
	{
		ft_putchar_fd(**var_value, 1);
		(*var_value)++;
		if (*(*var_value - 1) == '=')
			break;
	}
}

static
void	builtins_export_print(t_shell *shell)
{
	size_t	i;
	char	*var_value;

	i = 0;
	while (shell->export_vars.m_array[i] != NULL)
	{
		var_value = shell->export_vars.m_array[i];
		ft_putstr_fd("declare -x ", 1);
		builtins_export_printvar(&var_value);
		ft_printf("\"%s\"\n", var_value);
		i++;
	}
}

void	builtins_export(t_shell *shell, char **argv)
{
	if (argv[0] != NULL)
	{
		if (argv[1] == NULL)
			builtins_export_print(shell);
	}
}
