#include "../minishell.h"

int	builtins_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (perror("getcwd"), 1);
	if (ft_printf("%s\n", current_dir) < 0)
		return (-1);
	free(current_dir);
	return (0);
}