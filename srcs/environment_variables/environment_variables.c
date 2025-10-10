#include "environment_variables.h"

int     environment_variable_len(char *variable_name)
{
    int i;

    i = 0;
    while (variable_name[i] != '\0' && !ft_isspace(variable_name[1]))
        i++;
    return (1);
} 

char	**enviroment_variable_expand(char **envp, char *variable_name)
{
	int		i;
    int     variable_len;
	char	*path;
	char	**dirs;

	i = 0;
	path = NULL;
	dirs = NULL;
	while (envp[i])
	{
        variable_len = environment_variable_len(variable_name);
		if (ft_bool_strncmp(envp[i], variable_name, variable_len) == true)
			path = envp[i] + variable_len;
		i++;
	}
	dirs = ft_split(path, ':');
	if (dirs == NULL)
		error_exit("Failed to get path directories");
	return (dirs);
}
