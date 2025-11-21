/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:36:14 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/21 18:00:31 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../cleaning/cleaning.h"

void	buffer_realloc(t_shell *sh, char *buffer, int j, char **token_string)
{
	buffer[j] = '\0';
	free(*token_string);
	*token_string = ft_strdup(buffer);
	if (*token_string == NULL)
		exit_clean(sh, 66, NULL, buffer);
	free(buffer);
}

static inline void
	token_expansion_create(t_token_list *tok, char **token_string, t_shell *sh)
{
	t_iter	iter;
	char	*buffer;
	int		is_dquote;

	token_expansion_init(&iter, &buffer, &is_dquote);
	if (buffer == NULL)
		exit_clean(sh, 66, NULL, NULL);
	while ((*token_string)[iter.i] != '\0')
	{
		quoted_text_check((*token_string)[iter.i], &is_dquote, DQUOTE_LITERAL);
		if ((*token_string)[iter.i] == SQUOTE_LITERAL && is_dquote == -1)
			single_quotation_skip(buffer, *token_string, &iter);
		else if (is_variable(*token_string, iter.i) == true)
		{
			expansion_vars_handle(buffer, *token_string, &iter, sh);
			tok->is_var = true;
		}
		else
			buffer_fill(buffer, *token_string, &iter);
	}
	buffer_realloc(sh, buffer, iter.j, token_string);
}

void	token_expand(t_shell *sh)
{
	t_token_list	*tokens;

	tokens = sh->tokens;
	while (tokens != NULL)
	{
		if (tokens->token_type != TOKEN_LIMITER)
			token_expansion_create(tokens, &tokens->token_string, sh);
		tokens = tokens->next;
	}
}
