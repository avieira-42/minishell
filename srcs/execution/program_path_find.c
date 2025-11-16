#include "execution.h"

static
int	program_exists(char *program_path, char **result_path)
{
	if (access(program_path, X_OK | F_OK) == 0)
	{
		*result_path = program_path;
			return (1);
		/**result_path = ft_strdup(program_path);
		if (*result_path == NULL)
			return (-1); // SAFE EXIT*/
	}
	return (0);
}

static
int	program_path_get(const char *program_name, char **path, char **result)
{
	char	*program_path;
	char	*tmp;
	int		i;

	tmp = ft_strjoin("/", program_name);
	if (tmp == NULL)
		return (-1);
	i = 0;
	while (path[i] != NULL)
	{
		program_path = ft_strjoin(path[i], tmp);
		if (program_path == NULL)
			return (free(tmp), -1);
		if (program_exists(program_path, result))
			return (free(tmp), 1);
		free(program_path);
		++i;
	}
	return (free(tmp), 0);
}

int	program_path_find(char *program_name, char **path, char **result)
{
	if (program_name == NULL)
		return (-1);
	if (ft_strchr(program_name, '/') != NULL)
	{
		if (program_exists(program_name, result))
			return (3);
		return (2);
	}
	return (program_path_get(program_name, path, result));
}
