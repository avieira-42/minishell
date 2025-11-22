/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:43:32 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/21 11:14:25 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builtins.h"
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>

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

int	update_envs(char *old_dir, char **argv)
{
	int		i;
	char	current_dir[PATH_MAX];

	i = 0;
	getcwd(current_dir, PATH_MAX);
	while (argv[i] != NULL)
	{
		if (ft_strncmp("OLDPWD=", argv[i], 7) == 0)
		{
			free(argv[i]);
			argv[i] = ft_strjoin("OLDPWD=", old_dir);
		}
		else if (ft_strncmp("PWD=", argv[i], 4) == 0)
		{
			free(argv[i]);
			argv[i] = ft_strjoin("PWD=", current_dir);
		}
		if (argv[i] == NULL)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

void	update_envs_export(t_shell *shell, char *oldpwd)
{
	char	*export_args[3];
	char	current_dir[PATH_MAX];

	export_args[0] = "export";
	export_args[1] = ft_strjoin("OLDPWD=", oldpwd);
	if (export_args[1] == NULL)
		exit_clean(shell, 66, NULL, NULL);
	export_args[2] = NULL;
	builtins_export(shell, export_args);
	free(export_args[1]);
	getcwd(current_dir, PATH_MAX);
	export_args[1] = ft_strjoin("PWD=", current_dir);
	if (export_args[1] == NULL)
		exit_clean(shell, 66, NULL, NULL);
	builtins_export(shell, export_args);
	free(export_args[1]);
}

int	builtins_cd(char **argv, char **envp, t_shell *shell)
{
	char	*var_home;
	char	*path;
	char	current_dir[PATH_MAX];

	path = NULL;
	if (*argv == NULL)
	{
		var_home = env_get("HOME", envp);
		if (var_home == NULL)
			return (ft_error(EXIT_FAILURE, "HOME not set"));
		path = var_home;
	}
	if (**argv == '\0')
		return (EXIT_SUCCESS);
	else if (argv[1] != NULL)
		return (ft_error(EXIT_FAILURE, "too many arguments"));
	if (path == NULL)
		path = *argv;
	getcwd(current_dir, PATH_MAX);
	if (chdir(path) == -1)
		return (ft_error(EXIT_FAILURE, strerror(errno)));
	update_envs_export(shell, current_dir);
	return (EXIT_SUCCESS);
}
