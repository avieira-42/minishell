#include "../minishell.h"

int	array_count(char **array)
{
	int	i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i != NULL])
		++i;
	return (i);
}

void	free_array(void **array, int size, int free_all)
{
	if (array == NULL)
		return ;
	if (size < 0)
	{
		while (array != NULL)
		{
			free(*array);
			*array++ = NULL;
		}
	}
	else 
	{
		while (size-- > 0)
		{
			free(array[size]);
			array[size] = NULL;
		}
	}
	if (free_all)
		free(array);
}

char	**builtins_envp_copy(char **envp)
{
	const int		envp_len = array_count(envp);
	char			**envp_copy;
	int				i;

	if (envp == NULL)
		return (NULL);
	envp_copy = ft_calloc(envp_len + 1, sizeof(char *));
	if (envp_copy == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (envp_copy[i] == NULL)
			return (free_array((void **)envp_copy, i, TRUE), NULL);
		++i;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}

int	builtins_variable_get(char **envp, const char *variable_name)
{
	int		len_name;
	int		variable_position;

	if (envp == NULL || variable_name == NULL)
		return (-1);
	len_name = ft_strlen(variable_name);
	variable_position = 0;
	while (envp[variable_position] != NULL)
	{
		if (ft_strncmp(envp[variable_position], variable_name, len_name) == 0)
			break ;
		++variable_position;
	}
	return (variable_position);
}

char	**builtins_variable_set(char **envp, const char *variable_name)
{
	int	variable_position;

	if (envp == NULL || variable_name == NULL)
		return (NULL);
	variable_position = builtins_variable_get(envp, variable_name);
	if (variable_position == -1)
		return (NULL);
}

char	**builtins_variable_unset(char	**envp, const char *variable_name);

char	**builtins_envp_append(char **envp, const char *variable);