#include "../minishell.h"

static
int	ft_error(int exit_code, char *error_msg)
{
	ft_printf_fd(STDERR_FILENO, "minishell: cd: %s\n", error_msg);
	return (exit_code);
}

char	*env_get(char *var_name, char **envp)
{
	int	var_len;
	int	i;

	if (envp == NULL)
		return (NULL);
	var_len = ft_strlen(var_name);
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(var_name, envp[i], var_len) == 0
	  		&& envp[i][var_len] == '=')
			return (envp[i] + var_len + 1);
		++i;
	}
	return (NULL);
}

int	builtins_cd(char **argv, char **envp)
{
	char	*var_home;

	if (*argv == NULL)
	{
		var_home = env_get("HOME", envp);
		if (var_home == NULL)
			return (ft_error(EXIT_FAILURE, "HOME not set"));
		*argv = var_home;
	}
	else if (argv[1] != NULL)
		return (ft_error(EXIT_FAILURE, "too many arguments"));
	if (chdir(*argv) == -1)
		return (ft_error(EXIT_FAILURE, strerror(errno)));
	return (EXIT_SUCCESS);
}
