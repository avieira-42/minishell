#include "../minishell.h"

static
int	is_flag(char *str)
{
	while (*str)
	{
		if (*str++ != 'n')
			return (0);
	}
	return (1);
}

static
int	echo_write(char **user_input, const char *append)
{
	char	*sep;

	sep = " ";
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

int	builtins_echo(char **user_input)
{
	const char	*flag = "-";
	const int	len_flag = ft_strlen(flag);
	int			i;

	i = 0;
	while (user_input[i] && ft_strncmp(user_input[i], flag, len_flag) == 0)
	{
		if (!is_flag(user_input[i] + 1))
			break ;
		++i;
	}
	if (i > 0)
		return (echo_write(&user_input[i], ""));
	return (echo_write(&user_input[i], "\n"));
}
