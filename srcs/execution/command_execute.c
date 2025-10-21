#include "../minishell.h"

int	command_exists(t_command *command, char **command_path, char **envp)
{
	int	exit_code;

	*command_path = NULL;
	exit_code = program_path_find(command->argv[0], NULL, &command_path);
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
	return (0);
}

int	command_execute(t_command *command, char **envp)
{
	char	*command_path;
	
	if (command_exists(command, &command_path, envp) == 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);

}
