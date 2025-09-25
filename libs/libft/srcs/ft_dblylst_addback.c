/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblylst_addback.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:40:18 by avieira-          #+#    #+#             */
/*   Updated: 2025/09/25 00:46:31 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h" 

void	ft_dblylst_addback(t_dblylst *dblylst, t_dblylst *new_node)
{
	t_dblylst	*last;

	last = ft_dblylst_last(dblylst);
	dblylst->prev = new_node;
	last->next = new_node;
	new_node->prev = last;
	new_node->next = dblylst;
}
