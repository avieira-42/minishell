/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_path_find.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:49:45 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:49:50 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "../cleaning/cleaning.h"
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

static
int	program_exists(char *program_path, char **result_path, int print_error)
{
	int	exit_code;

	if (access(program_path, X_OK | F_OK) == 0)
	{
		*result_path = program_path;
		return (1);
	}
	exit_code = 0;
	if (print_error == TRUE)
	{
		if (errno == EACCES)
			exit_code = 126;
		if (errno == ENOENT)
			exit_code = 127;
		ft_printf_fd(STDERR_FILENO,
			"minishell: %s: %s\n", program_path, strerror(errno));
	}
	return (exit_code);
}

static
int	program_path_get(const char *program_name, char **path, char **result)
{
	char	*program_path;
	char	*tmp;
	int		i;

	if (path == NULL || *program_name == '\0')
		return (0);
	tmp = ft_strjoin("/", program_name);
	if (tmp == NULL)
		return (-1);
	i = 0;
	while (path[i] != NULL)
	{
		program_path = ft_strjoin(path[i], tmp);
		if (program_path == NULL)
			return (free(tmp), -1);
		if (program_exists(program_path, result, FALSE) == TRUE)
			return (free(tmp), 1);
		free(program_path);
		++i;
	}
	return (free(tmp), 0);
}

int	program_path_find(t_command *command, char **command_path, char **envp)
{
	char	**path_env;
	int		exit_code;

	path_env = ft_split(env_get("PATH", envp), ':');
	*command_path = NULL;
	exit_code = program_path_get(command->argv[0], path_env, command_path);
	free_array((void **)path_env, -1, TRUE);
	if (exit_code == ALLOC_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, ALLOC_ERROR);
		return (EXIT_FAILURE);
	}
	else if (exit_code == NOT_FOUND_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NOT_FOUND_ERROR, command->argv[0]);
		return (EXIT_NOT_FOUND);
	}
	return (EXIT_SUCCESS);
}

int	absolute_path_check(char *command_path, char **result_path)
{
	int	exit_code;

	exit_code = program_exists(command_path, result_path, TRUE);
	if (exit_code == 1)
		return (EXIT_SUCCESS);
	return (exit_code);
}

int	command_exists(t_command *command, char **command_path, char **envp)
{
	if (command->argv[0] == NULL)
		return (-1);
	if (ft_strchr(command->argv[0], '/') != NULL)
		return (absolute_path_check(command->argv[0], command_path));
	return (program_path_find(command, command_path, envp));
}
