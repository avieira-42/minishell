/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:37:08 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/20 19:37:08 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "../cleaning/cleaning.h"

void	command_exit_clear(t_btree **tree_node)
{
	if (tree_node != NULL)
	{
		if ((*tree_node)->command != NULL)
		{
			if ((*tree_node)->command->argv != NULL)
				free((*tree_node)->command->argv);
			if ((*tree_node)->command->redirects != NULL)
				redirect_clear_safe((*tree_node)->command->redirects);
			free((*tree_node)->command);
			(*tree_node)->command = NULL;
		}
		btree_clear(tree_node);
		*tree_node = NULL;
	}
}

void	command_clear_safe(t_command *command)
{
	if (command->redirects != NULL)
		redirect_clear_safe(command->redirects);
	if (command->argv != NULL)
	{
		free(command->argv);
		command->argv = NULL;
	}
	free (command);
}

void	command_clear(t_command *command)
{
	if (command->redirects != NULL)
		redirect_clear(command->redirects);
	if (command->argv != NULL)
		free_array((void **)command->argv, -1, true);
	free (command);
}
