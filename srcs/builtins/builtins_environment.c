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

char	**builtins_envp_copy(char **envp)
{
	char	**envp_copy;

	if (!envp)
		return (NULL);
}