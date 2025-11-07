#include "../minishell.h"
#include <stdlib.h>
#include <unistd.h>

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
	char	*var_old_pwd;

	(void)envp;
	if (*argv == NULL)
	{
		var_home = env_get("HOME", envp);
		if (var_home == NULL)
		{
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);	
			return (EXIT_FAILURE);
		}
		*argv = var_home;
	}
	var_old_pwd = env_get("OLDPWD", envp);
	if (chdir(*argv) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: cd: %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	return (0);
}
