/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:37:13 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/20 19:37:14 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "../cleaning/cleaning.h"

void	redirect_clear_safe(t_redirect *redirs)
{
	t_redirect	*tmp;

	tmp = NULL;
	while (redirs != NULL)
	{
		if (redirs->redir_type == TOKEN_HEREDOC)
			safe_close(&(redirs->fd));
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}

void	redirect_clear(t_redirect *redirs)
{
	t_redirect	*tmp;

	tmp = NULL;
	while (redirs != NULL)
	{
		if (redirs->redir_type == TOKEN_HEREDOC)
			safe_close(&(redirs->fd));
		if (redirs->filename != NULL)
			free (redirs->filename);
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}
