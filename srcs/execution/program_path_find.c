#include "execution.h"
#include "../cleaning/cleaning.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static
int	program_exists(char *program_path, char **result_path, int print_error)
{
	(void)print_error;
	if (access(program_path, X_OK | F_OK) == 0)
	{
		*result_path = program_path;
		return (1);
	}
	//if (print_error == TRUE)
	//	ft_printf_fd(STDERR_FILENO, "minishell: %s: %s\n", program_path, strerror(errno));
	return (0);
}

static
int	program_path_get(const char *program_name, char **path, char **result)
{
	char	*program_path;
	char	*tmp;
	int		i;

	if (*program_name == '\0')
		return (0);
	tmp = ft_strjoin("/", program_name);
	if (tmp == NULL)
		return (-1);
	i = 0;
	while (path[i] != NULL)
	{
		program_path = ft_strjoin(path[i], tmp);
		if (program_path == NULL)
			return (free(tmp), -1);
		if (program_exists(program_path, result, FALSE) == TRUE)
			return (free(tmp), 1);
		free(program_path);
		++i;
	}
	return (free(tmp), 0);
}

static
int	program_path_find(char *program_name, char **path, char **result)
{

	if (program_name == NULL)
		return (-1);
	if (ft_strchr(program_name, '/') != NULL)
	{
		if (program_exists(program_name, result, TRUE) == 1)
			return (3);
		return (2);
	}
	return (program_path_get(program_name, path, result));
}

int	command_exists(t_command *command, char **command_path, char **envp)
{
	char	**path_env;
	int		exit_code;

	path_env = ft_split(env_get("PATH", envp), ':');
	*command_path = NULL;
	exit_code = program_path_find(command->argv[0], path_env, command_path);
	free_array((void **)path_env, -1, TRUE);
	if (exit_code == ALLOC_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, ALLOC_ERROR);
		return (EXIT_FAILURE);
	}
	else if (exit_code == NOT_FOUND_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NOT_FOUND_ERROR, command->argv[0]);
		return (EXIT_NOT_FOUND);
	}
	else if (exit_code == NO_FILE_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NO_FILE_ERROR, command->argv[0]);
		return (EXIT_NOT_FOUND);
	}
	else if (exit_code == 4)
	{
		ft_printf_fd(STDERR_FILENO, DIR_ERR, command->argv[0]);
		return (126);
	}
	return (EXIT_SUCCESS);
}
