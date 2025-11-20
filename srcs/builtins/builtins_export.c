/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:38:04 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/20 19:38:04 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../cleaning/cleaning.h"

static	inline
void	builtins_export_printvar(char **var_value)
{
	while (**var_value != '\0')
	{
		ft_putchar_fd(**var_value, 1);
		(*var_value)++;
		if (*(*var_value - 1) == '=')
			break ;
	}
}

static
void	builtins_export_print(t_shell *shell)
{
	size_t	i;
	char	*var_value;

	i = 0;
	while (shell->export_vars.m_array[i] != NULL)
	{
		var_value = shell->export_vars.m_array[i];
		ft_putstr_fd("declare -x ", 1);
		builtins_export_printvar(&var_value);
		if (*(var_value - 1) == '=')
			ft_printf("\"%s\"\n", var_value);
		else
			write(1, "\n", 1);
		i++;
	}
	shell->exit_code = 0;
}

static inline
int	builtins_export_is_valid_var_name(char *argv, char **var_end)
{
	if (*argv != '_' && ft_isalpha(*argv) == false)
		return (-1);
	while (*argv != '=' && *argv != '\0')
	{
		if (*argv != '_' && ft_isalnum(*argv) == false)
			return (-1);
		argv++;
	}
	*var_end = argv;
	return (0);
}

int	builtins_export(t_shell *shell, char **argv)
{
	char	*var;
	char	*var_end;

	shell->exit_code = 0;
	if (*(++argv) == NULL)
		builtins_export_print(shell);
	while (*argv != NULL)
	{
		var = ft_strdup(*argv);
		if (var == NULL)
			exit_clean(shell, 66, NULL, NULL);
		if (builtins_export_is_valid_var_name(*argv, &var_end) == -1)
		{
			ft_printf_fd(2, EXPORT_ERROR, *argv);
			shell->exit_code = 1;
			free (var);
		}
		else
			builtins_export_addvar(shell, var, *argv, var_end);
		argv++;
	}
	return (shell->exit_code);
}
