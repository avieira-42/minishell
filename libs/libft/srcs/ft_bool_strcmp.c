/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool_strcmp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-soeiro <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:31:53 by a-soeiro          #+#    #+#             */
/*   Updated: 2025/09/11 19:13:20 by a-soeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_bool	ft_bool_strcmp(char *string_1, char *string_2)
{
	if (ft_strcmp(string_1, string_2) == 0)
		return (TRUE);
	return (FALSE);
}
