#include "../minishell.h"

int	array_count(char **array)
{
	int	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		++i;
	return (i);
}

void	free_array(void **array, int size, int free_all)
{
	if (!array)
		return ;
	if (size < 0)
	{
		while (*array)
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

	if (!envp)
		return (NULL);
	envp_copy = ft_calloc(envp_len + 1, sizeof(char *));
	if (!envp_copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
			return (free_array(envp_copy, i, TRUE), NULL);
		++i;
	}
}
