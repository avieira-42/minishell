#include "execution.h"

static
int	program_exists(char *program_path, char **result_path)
{
	if (access(program_path, X_OK | F_OK) == 0)
	{
		*result_path = program_path;
		return (1);
	}
	return (0);
}

static
int	program_path_get(const char *program_name, char **exec_paths, char **result_path)
{
	char	*program_path;
	char	*tmp;
	int		i;

	tmp = ft_strjoin("/", program_name);
	if (tmp == NULL)
		return (-1);
	i = 0;
	while (exec_paths[i] != NULL)
	{
		program_path = ft_strjoin(exec_paths[i], tmp);
		if (program_path == NULL)
			return (free(tmp), -1);
		if (program_exists(program_path, result_path))
			return (free(tmp), 1);
		free(program_path);
		++i;
	}
	return (free(tmp), 0);
}

int	program_path_find(char *program_name, char **exec_paths, char **result_path)
{
	if (program_name == NULL)
		return (-1);
	if (ft_strchr(program_name, '/') != NULL)
	{
		if (program_exists(program_name, result_path))
			return (1);
		return (2);
	}
	return(program_path_get(program_name, exec_paths, result_path));
}
