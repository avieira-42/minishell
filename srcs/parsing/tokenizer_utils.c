/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:36:49 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/20 19:36:50 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../types.h"

void	tokenize_dquoted_text(t_token_list **tokens, char *user_input, int *i)
{
	(*i)++;
	while (user_input[*i] != '\0' && user_input[*i] != DQUOTE_LITERAL)
		(*i)++;
	if (user_input[*i] != '\0')
		(*i)++;
	if (user_input[*i] == DQUOTE_LITERAL)
		tokenize_dquoted_text(tokens, user_input, i);
	else if (user_input[*i] == SQUOTE_LITERAL)
		tokenize_squoted_text(tokens, user_input, i);
}

void	tokenize_squoted_text(t_token_list **tokens, char *user_input, int *i)
{
	(*i)++;
	while (user_input[*i] != '\0' && user_input[*i] != SQUOTE_LITERAL)
		(*i)++;
	if (user_input[*i] != '\0')
		(*i)++;
	if (user_input[*i] == DQUOTE_LITERAL)
		tokenize_dquoted_text(tokens, user_input, i);
	else if (user_input[*i] == SQUOTE_LITERAL)
		tokenize_squoted_text(tokens, user_input, i);
}

void	tokenize_operator_set(t_token_list *token_node_new, char *c, int *i)
{
	if (ft_bool_strncmp(c, HEREDOC, 2) == true)
	{
		token_node_new->token_string = ft_strdup(HEREDOC);
		(*i)++;
	}
	else if (ft_bool_strncmp(c, APPEND, 2) == true)
	{
		token_node_new->token_string = ft_strdup(APPEND);
		(*i)++;
	}
	else if (*c == PIPE)
		token_node_new->token_string = ft_strdup(STRING_PIPE);
	else if (*c == REDIRECT_IN)
		token_node_new->token_string = ft_strdup(STRING_REDIRECT_IN);
	else if (*c == REDIRECT_OUT)
		token_node_new->token_string = ft_strdup(STRING_REDIRECT_OUT);
}
