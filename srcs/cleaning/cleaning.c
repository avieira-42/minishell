/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:44:31 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:49:08 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../binary_tree/binary_tree.h"
#include "../cleaning/cleaning.h"

void	iteration_clear(t_shell *shell)
{
	if (shell->tree != NULL)
		btree_clear(&shell->tree);
	if (shell->tokens != NULL)
		ft_token_lst_clear(&shell->tokens);
	str_merge_sort(shell->export_vars, &shell->merge_ret);
	if (shell->merge_ret == -1)
		exit_clean(shell, 66, NULL, NULL);
}
