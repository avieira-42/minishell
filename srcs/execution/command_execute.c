#include "../minishell.h"

int	command_exists(t_command *command, char **command_path)
{
	char	**path_env;
	int		exit_code;

	path_env = ft_split(getenv("PATH"), ':');
	*command_path = NULL;
	exit_code = program_path_find(command->argv[0], path_env, command_path);
	free_array((void **)path_env, -1, TRUE);
	if (exit_code == -1)
	{
		ft_printf_fd(2, "error: could not allocate memory\n");
		return (0);
	}
	else if (exit_code == 0)
	{
		ft_printf_fd(2, "%s: command not found\n", command->argv[0]);
		return (0);
	}
	else if (exit_code == 2)
	{
		ft_printf_fd(2, "minishell: %s: No such file or directory\n", command->argv[0]);
		return (0);
	}
	return (1);
}

int	command_execute(t_command *command, char **envp)
{
	char	*command_path;
	
	if (command_exists(command, &command_path) == 0)
		return (EXIT_FAILURE);
	(void)envp;
	execve(command_path, command->argv, envp);
	perror("execve");
	free(command_path);
	return (EXIT_FAILURE);
}
