# include "../../libs/libft/include/libft.h"
# include "../parsing/parsing.h"
# include "../types.h"

void
builtins_export_add_to_vars(t_shell *shell, char *var, t_str_array *vars)
{
	vars->m_array = ft_realloc(vars->m_array,
			sizeof(char *) * (vars->length + 2),
			sizeof(char *) * (shell->export_vars.length + 1));
	if (vars->m_array == NULL)
		return (free(var)) ; // SAFE EXIT
	shell->export_vars.m_array[vars->length] = var;
	shell->export_vars.m_array[vars->length + 1] = NULL;
	vars->length++;
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
            /*&& vars->m_array[i][len] == '='*/)
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
	builtins_export_add_to_vars(shell, var, vars);
}

void
builtins_export_add_to_env(t_shell *shell, char *var, char **vars)
{
	shell->env_vars = ft_realloc(vars,
			sizeof (char *) * (shell->env_size + 2),
			sizeof(char *) * (shell->env_size + 1));
	if (shell->env_vars == NULL)
		return (free(var)); // SAFE EXIT
	shell->env_vars[shell->env_size] = ft_strdup(var);
	if (shell->env_vars[shell->env_size] == NULL)
		return ; // SAFE EXIT
	shell->env_vars[shell->env_size + 1] = NULL;
	shell->env_size++;
}

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
}

void
builtins_export_addvar(t_shell *shell, char *var, char *argv, char *end)
{
	size_t	var_len;

	var_len = environment_variable_len(var);
	if (*argv == '_' && end == argv + 1)
		return (free(var));
	if (*end == '=')
		builtins_export_to_env(shell, var, var_len);
	builtins_export_to_vars(shell, var, end, var_len);
}
