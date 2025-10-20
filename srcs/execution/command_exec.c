#include "../minishell.h"

const char *program_path_find(char *program_name, char **exec_paths)
{
	char	*program_path;
	int		i;
	if (program_name == NULL)
		return (NULL);
	if (ft_strchr(program_name, '/') != NULL)
		return (program_name);
	i = 0;
	while (exec_paths[i] != NULL)
	{
		program_path = ft_strjoin(exec_paths[i], program_name);
		if (program_path == NULL)
			return (NULL);
		if (access(program_path, X_OK) == 0)
			return (program_path);
	}
	return(program_path);
}
