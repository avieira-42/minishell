#include "../minishell.h"

int echo(char *input, char flag)
{
	ft_printf(input);
	if (flag != 'n')
		ft_printf("\n");
	return (0);
}

int	echo_flags_check(char *input)
{
	const char *command = "echo";
	const char *flag = "-n";
	const int	len_command = ft_strlen(command);
	const int	len_flag = ft_strlen(flag);

	if (ft_strncmp(input, command, len_command != 0))
		return (1);
	input += len_command + 1;
	if (ft_strncmp(input, flag, len_flag) == 0)
		echo(input + len_flag + 1, 'n');
	else
		echo(input, 0);
}