#include "../minishell.h"

int	command_exists(t_command *command, char **command_path)
{
	char	**split_path_env;
	char	*path_env;
	int		exit_code;

	path_env = getenv("PATH");
	split_path_env = ft_split(path_env, ':');
	*command_path = NULL;
	exit_code = program_path_find(command->argv[0], split_path_env, command_path);
	free_array((void **)split_path_env, -1, TRUE);
	if (exit_code == -1)
	{
		ft_printf_fd(2, "error: could not allocate memory\n");
		return (0);
	}
	else if (exit_code == 1)
	{
		ft_printf_fd(2, "%s: command not found\n", command->argv[0]);
		return (0);
	}
	return (1);
}

int	command_execute(t_command *command, char **envp)
{
	char	*command_path;
	
	if (command_exists(command, &command_path) == 0)
		return (EXIT_FAILURE);
	execve(command_path, command->argv, envp);
	perror("execve");
	return (EXIT_FAILURE);
}
