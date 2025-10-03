/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool_strncmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-soeiro <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 18:31:53 by a-soeiro          #+#    #+#             */
/*   Updated: 2025/10/03 18:29:37 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

bool	ft_bool_strncmp(char *string_1, char *string_2, int n)
{
	if (ft_strncmp(string_1, string_2, n) == 0)
		return (true);
	return (false);
}
