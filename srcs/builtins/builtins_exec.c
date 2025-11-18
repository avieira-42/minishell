#include "../minishell.h"

int	builtins_exec(char **argv, char **envp, t_shell *shell)
{
	(void)envp;
	if (argv == NULL)
		return (-1);
	if (*argv != NULL && ft_strcmp(argv[0], "echo") == 0)
		return (builtins_echo(&argv[1]));
	else if (*argv != NULL && ft_strcmp(argv[0], "pwd") == 0)
		return (builtins_pwd());
	else if (*argv != NULL && ft_strcmp(argv[0], "cd") == 0)
		return (builtins_cd(&argv[1], shell->env_vars, shell));
	else if (*argv != NULL && ft_strcmp(argv[0], "export") == 0)
		return (builtins_export(shell, argv));
	else if (*argv != NULL && ft_strcmp(argv[0], "unset") == 0)
		return (builtins_unset(shell, argv + 1));
	else if (*argv != NULL && ft_bool_strcmp(argv[0], CMD_AUTHORS) == TRUE)
		return (builtins_authors());
	else if (*argv != NULL && ft_bool_strcmp(argv[0], CMD_LOGO) == TRUE)
		return (builtins_logo());
	else if (*argv != NULL && ft_strcmp(argv[0], "exit") == 0)
		return (builtins_exit(argv + 1, shell));
	else
		return (-1);
}
