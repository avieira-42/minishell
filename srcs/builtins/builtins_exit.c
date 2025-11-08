#include "../minishell.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

static
int	ft_error(int exit_code, char *arg, char *error_msg)
{
	if (arg != NULL)
		ft_printf_fd(
			STDERR_FILENO,
			"minishell: exit: %s: %s\n",
			arg, error_msg);
	else
		ft_printf_fd(STDERR_FILENO, "minishell: exit: %s\n", error_msg);
	return (exit_code);
}

static
int	is_overflow(long number, int digit, int sign)
{
	if (sign == -1)
		return (number < LONG_MIN / 10 || (number == LONG_MIN / 10
				&& digit > -(LONG_MIN % 10)));
	return (number > LONG_MAX / 10 || (number == LONG_MAX / 10
			&& digit > LONG_MAX % 10));
}

static
int	number_get(char *str, int *position, long *result, int sign)
{
	int		digit;

	while (ft_isdigit(str[*position]))
	{
		digit = str[*position] - '0';
		if (is_overflow(*result, digit, sign) == TRUE)
			return (ft_error(EXIT_FAILURE, str, "numeric argument required"));
		if (sign == -1)
			*result = *result * 10 - digit;
		else
			*result = *result * 10 + digit;
		++*position;
	}
	return (EXIT_SUCCESS);
}

static
long	ft_strtol(char *str)
{
	long	result;
	int		sign;
	int		i;

	i = 0;
	while (ft_isspace(str[i]) != 0)
		++i;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	if (ft_isdigit(str[i]) == 0)
		return (ft_error(EXIT_FAILURE, str, "numeric argument required"));
	if (number_get(str, &i, &result, sign) == EXIT_FAILURE)
		return (2);
	while (ft_isspace(str[i]) != 0)
		++i;
	if (str[i] != '\0')
		return (ft_error(2, str, "numeric argument required"));
	return (result);
}

int	builtins_exit(char **argv)
{
	t_byte	exit_status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (argv[0] == NULL)
		exit(EXIT_SUCCESS);
	else if (argv[1] != NULL)
		return (ft_error(EXIT_FAILURE, NULL, "too many arguments"));
	exit_status = ft_strtol(argv[0]);
	ft_printf("exit_status = %d\n", exit_status);
	exit(exit_status);
}
