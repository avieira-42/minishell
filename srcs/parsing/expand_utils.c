/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:36:21 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/23 17:38:38 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../cleaning/cleaning.h"

void	single_quotation_skip(char *buffer, char *token_str, t_iter *iter)
{
	buffer[iter->j] = token_str[iter->i];
	(iter->i)++;
	(iter->j)++;
	while (token_str[iter->i] != SQUOTE_LITERAL && token_str[iter->i] != '\0')
	{
		buffer[iter->j] = token_str[iter->i];
		(iter->i)++;
		(iter->j)++;
	}
	buffer[iter->j] = token_str[iter->i];
	if (token_str[iter->i] == '\0')
		return ;
	(iter->i)++;
	(iter->j)++;
}

int	expansion_vars_handle_special(char *buf, char *token,
			t_iter *iter, t_shell *shell)
{
	char	*exp;

	exp = NULL;
	if (ft_bool_strncmp(&token[iter->i], "$?", 2) == true)
		exp = ft_itoa(shell->exit_code);
	else if (ft_bool_strncmp(&token[iter->i], "$$", 2) == true)
		exp = ft_itoa(get_my_pid());
	else if (ft_bool_strncmp(&token[iter->j], "$0", 2) == true)
		exp = ft_strdup("minishell");
	else
		return (-1);
	if (exp == NULL)
		exit_clean(shell, 66, NULL, buf);
	iter->i += 2;
	ft_memcpy(&buf[iter->j], exp, ft_strlen(exp));
	iter->j += ft_strlen(exp);
	free(exp);
	return (0);
}

void
	expansion_vars_handle(char *buf, char *token, t_iter *iter, t_shell *shell)
{
	char	*exp;

	if (expansion_vars_handle_special(buf, token, iter, shell) == -1)
	{
		exp = environment_variable_get(shell->env_vars,
				&token[iter->i], &(iter->i));
		ft_memcpy(&buf[iter->j], exp, ft_strlen(exp));
		iter->j += ft_strlen(exp);
	}
}

void	token_expansion_init(t_iter *iter, char **buffer, int *double_quoted)
{
	iter->i = 0;
	iter->j = 0;
	*double_quoted = -1;
	*buffer = malloc(107374182);
}

void	buffer_fill(char *buffer, char *token_string, t_iter *iter)
{
	buffer[iter->j] = token_string[iter->i];
	iter->i++;
	iter->j++;
}
