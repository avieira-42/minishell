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
		if (*(var_value - 1) == '=')
			ft_printf("\"%s\"\n", var_value);
		else
			write(1, "\n", 1);
		i++;
	}
	shell->exit_code = 0;
}

static inline
int	builtins_export_is_valid_var_name(char *argv, char **var_end)
{
	if (*argv != '_' && ft_isalpha(*argv) == false)
		return (-1);
	while (*argv != '=' && *argv != '\0')
	{
		if (*argv != '_' && ft_isalnum(*argv) == false)
			return (-1);
		argv++;
	}
	*var_end = argv;
	return (0);
}

void
builtins_export_to_vars(t_shell *shell, char *var, char *var_end, size_t len)
{
	size_t		i;
	t_str_array	*vars;

	i = 0;
	vars = &shell->export_vars;
	while (vars->m_array[i] != NULL)
	{
		if (ft_bool_strncmp(vars->m_array[i], var, len) == true
            && vars->m_array[i][len] == '=')
        {
			if (*var_end == '=')
			{
				free(vars->m_array[i]);
				vars->m_array[i] = var;
			}
			return ;
        }
		i++;
	}
	vars->m_array = ft_realloc(vars->m_array,
			sizeof(char *) * (vars->length + 1),
			sizeof(char *) * shell->export_vars.length);
	if (vars->m_array == NULL)
		return (free(var)) ; // SAFE EXIT
	vars->m_array[vars->length] = var;
	vars->m_array[vars->length + 1] = NULL;
	vars->length++;
}

static inline
void	builtins_export_to_env(t_shell *shell, char *var, size_t len)
{
	size_t	i;
	char	**vars;

	i = 0;
	vars = shell->env_vars;
	while (vars[i] != NULL)
	{
		if (ft_bool_strncmp(vars[i], var, len) == true
				&& shell->env_vars[i][len] == '=')
		{
			free(vars[i]);
			vars[i] = var;
			return ;
		}
		i++;
	}
	shell->env_vars = ft_realloc(vars,
			sizeof (char *) * (shell->env_size + 1),
			sizeof(char *) * shell->env_size);
	if (shell->env_vars == NULL)
		return (free(var)); // SAFE EXIT
	shell->env_vars[shell->env_size] = var;
	shell->env_vars[shell->env_size + 1] = NULL;
	shell->env_size++;
}

static inline void
builtins_export_add_var(t_shell *shell, char *var, char *argv, char *var_end)
{
	size_t	var_len;

	var_len = environment_variable_len(var);
	if (*argv == '_' && var_end == argv + 1)
		return (free(var));
	if (*var_end == '=')
		builtins_export_to_env(shell, var, var_len);
	builtins_export_to_vars(shell, var, var_end, var_len);
}

void	builtins_export(t_shell *shell, char **argv)
{
	char	*var;
	char	*var_end;

	if (*(++argv) == NULL)
		return (builtins_export_print(shell));
	while (*argv != NULL)
	{
		var = ft_strdup(*argv);
		if (var == NULL)
			return ; // SAFE EXIT
		if (builtins_export_is_valid_var_name(*argv, &var_end) == -1)
		{
			ft_printf_fd(2, EXPORT_ERROR, *argv);
			shell->exit_code = 1;
			free (var);
		}
		else
			builtins_export_add_var(shell, var, *argv, var_end);
		argv++;
	}
}
