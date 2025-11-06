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
	shell->exit_code = 0;
}

static
int	builtins_export_is_valid_var_name(char *argv)
{
	if (*argv != '_' || ft_isalpha(*argv) == false)
		return (-1);
	while (*argv != '=' && *argv != '\0')
	{
		if (*argv != '_' || ft_isalnum(*argv) == false)
			return (-1);
		argv++;
	}
	return (0);
}

void	builtins_export(t_shell *shell, char **argv)
{
	bool	invalid_var;
	char	*var;

	invalid_var = false;
	if (*(++argv) == NULL)
	{
		builtins_export_print(shell);
		return ;
	}
	while (*argv != NULL)
	{
		if (builtins_export_is_valid_var_name(*argv) == -1)
		{
			ft_printf_fd(2, EXPORT_ERROR, *argv);
			shell->exit_code = 1;
			invalid_var = true;
		}
		else
		{
			var = malloc(sizeof(char) * ft_strlen(
		}
		argv++;
	}
}
