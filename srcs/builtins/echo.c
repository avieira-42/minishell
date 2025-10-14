#include "../minishell.h"

static
int echo_write(char **user_input, const char *append)
{
	char	*sep = " ";

	while (*user_input)
	{
		if (*(user_input + 1) == NULL)
			sep = "";
		if (ft_printf("%s%s", *user_input++, sep) < 0)
			return (-1);
	}
	if (write(1, append, ft_strlen(append)) == -1)
		return (-1);
	return (0);
}

int	echo(char **user_input)
{
	const char *command = "echo";
	const char *flag = "-n";
	const int	len_command = ft_strlen(command);
	const int	len_flag = ft_strlen(flag);

	if (ft_strncmp(user_input[0], command, len_command != 0))
		return (1);
	if (ft_strncmp(user_input[1], flag, len_flag) == 0)
		return (echo_write(&user_input[2], ""));
	return (echo_write(&user_input[1], "\n"));
}