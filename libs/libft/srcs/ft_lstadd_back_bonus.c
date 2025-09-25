/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 00:05:23 by jesusoncrac       #+#    #+#             */
/*   Updated: 2025/09/25 00:44:27 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	if (new_node)
	{
		if (*lst)
			ft_lstlast(*lst)->next = new_node;
		else
			*lst = new_node;
	}
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		i;
	(void)	argc;
	t_list	*lst;
	t_list	*node;

	i = 1;
	lst = NULL;
	while (i < argc)
	{
		node = ft_lstnew(argv[i]);
		ft_lstadd_back(&lst, node);
		i++;
		node = node->next;
	}
	node = NULL;
	while (lst)
	{
		printf("%s ", (char *) lst->content);
		lst = lst->next;
	}
}*/
