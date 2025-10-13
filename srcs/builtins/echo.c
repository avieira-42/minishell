#include "../minishell.h"

static
int echo_write(char *input, const char *append)
{
	if (write(1, input, ft_strlen(input)) == -1)
		return (-1);
	if (write(1, append, ft_strlen(append)) == -1)
		return (-1);
	return (0);
}

int	echo(char *input)
{
	const char *command = "echo";
	const char *flag = "-n";
	const int	len_command = ft_strlen(command);
	const int	len_flag = ft_strlen(flag);

	if (ft_strncmp(input, command, len_command != 0))
		return (1);
	input += len_command + 1;
	if (ft_strncmp(input, flag, len_flag) == 0)
		return (echo_write(input + len_flag + 1, ""));
	return (echo_write(input, "\n"));
}