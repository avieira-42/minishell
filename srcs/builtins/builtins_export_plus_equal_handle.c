/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_plus_equal_handle.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:51:06 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/21 17:52:07 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cleaning/cleaning.h"
#include "../parsing/parsing.h"

static
void	builtins_export_var_expand(t_shell *shell, char **var,
			char *var_value, char *tmp)
{
	t_iter	iter;
	char	*buf;
	char	*exp;
	char	*var_tmp;

	buf = malloc(107374182);
	if (buf == NULL)
		exit_clean(shell, 66, NULL, *var);
	iter.i = 0;
	exp = environment_variable_get(shell->env_vars, tmp, &iter.i);
	iter.i = 0;
	iter.j = 0;
	while (var[0][iter.i] != '=')
		buf[iter.j++] = var[0][iter.i++];
	iter.i = 0;
	buf[iter.j++] = '=';
	while (exp[iter.i] != '\0')
		buf[iter.j++]  = exp[iter.i++];
	iter.i = 1;
	while (var_value[iter.i] != '\0')
		buf[iter.j++] = var_value[iter.i++];
	var_tmp	= *var;
	buffer_realloc(shell, buf, iter.j, var);
}

void	builtins_export_var_setup(t_shell *shell, char **var, char *end)
{
	char	*op_add;
	char	tmp[99999];
	int		j;
	int		i;

	op_add = ft_strchr(*var, '+');
	end = ft_strchr(*var, '=');
	ft_memmove(op_add, end, sizeof(char) * ft_strlen(op_add));
	i = 0;
	j = 0;
	tmp[i] = '$';
	while (var[0][j] != '=')
		tmp[++i] = var[0][j++];
	tmp[++i] = '\0';
	builtins_export_var_expand(shell, var, op_add, tmp);
}

