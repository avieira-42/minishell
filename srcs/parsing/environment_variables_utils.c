/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variables_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:56:49 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/20 20:08:38 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/include/libft.h"
#include "../types.h"
#include "../cleaning/cleaning.h"

size_t	minishell_envp_size(t_shell *shell)
{
	size_t	size;

	size = 0;
	while (shell->envp[size])
		size++;
	return (size);
}

int
	shell_lvl_incr(t_shell *shell, char **new_var, char *old_var, char **tmp)
{
	int		lvl_int;

	(void) dup;
	lvl_int = ft_atoi(old_var + 6) + 1;
	if (lvl_int > 999)
	{
		if (shell->lvl_message == false)
		{
			shell->lvl_message = true;
			ft_printf_fd(2, LVLERR, lvl_int);
		}
		lvl_int = 1;
	}
	*tmp = ft_itoa(lvl_int);
	if (*tmp == NULL)
		return (-1);
	*new_var = ft_strjoin("SHLVL=", *tmp);
	free (*tmp);
	return (0);
}

void	shell_lvl_create(t_shell *shell, char **dup)
{
	dup[shell->env_size] = ft_strdup("SHLVL=1");
	if (dup[shell->env_size] == NULL)
		exit_clean(shell, 66, dup, NULL);
}

char	**minishell_env_dup(t_shell *shell, char *lvl)
{
	size_t	i;
	char	**dup;

	dup = malloc(sizeof(char *) * (shell->env_size + 2));
	if (dup == NULL)
		return (exit_clean(shell, 66, NULL, NULL), NULL);
	dup[shell->env_size] = NULL;
	dup[shell->env_size + 1] = NULL;
	i = 0;
	while (i < shell->env_size)
	{
		if (ft_bool_strncmp(shell->envp[i], "SHLVL", 5) == true)
		{
			if (shell_lvl_incr(shell, &dup[i], shell->envp[i], &lvl) == -1)
				return (exit_clean(shell, 66, dup, NULL), NULL);
		}
		else
			dup[i] = ft_strdup(shell->envp[i]);
		if (dup[i++] == NULL)
			return (exit_clean(shell, 66, dup, NULL), NULL);
		dup[i] = NULL;
	}
	if (lvl == NULL)
		shell_lvl_create(shell, dup);
	return (dup);
}
