/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:38:07 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/20 19:38:07 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static inline
size_t	builtins_unset_var_len(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] != '=' && var[i] != '\0')
		i++;
	return (i);
}

static
void	builtins_unset_from_matrix(char **vars, size_t *size, char *variable)
{
	size_t	i;
	size_t	var_len;

	i = 0;
	while (vars[i] != NULL)
	{
		var_len = builtins_unset_var_len(vars[i]);
		if (ft_bool_strncmp(vars[i], variable, var_len) == true)
		{
			free(vars[i]);
			ft_memmove(&vars[i], &vars[i + 1], sizeof(char **) * ((*size) - i));
			(*size)--;
			return ;
		}
		i++;
	}
}

int	builtins_unset(t_shell *shell, char **vars)
{
	t_str_array	*export;
	size_t		i;

	i = 0;
	export = &shell->export_vars;
	while (vars[i] != NULL)
	{
		builtins_unset_from_matrix(shell->env_vars, &shell->env_size, vars[i]);
		builtins_unset_from_matrix(export->m_array, &export->length, vars[i]);
		i++;
	}
	return (0);
}
