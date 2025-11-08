#include "../minishell.h"
#include <unistd.h>

typedef unsigned char t_byte;

long	ft_atol(char *str)
{
	long	result;

	while (ft_isspace(*str) != 0)
		++str;
}

void	builtins_exit(char **argv)
{
	t_byte	i;

	if (argv[0] == NULL)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		exit(EXIT_SUCCESS);
	}
	i = ft_atoi(argv[1]);
	ft_putendl_fd("exit", STDERR_FILENO);
	ft_printf("i = %d\n", i);
	exit (i);
}
