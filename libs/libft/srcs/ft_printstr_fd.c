/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 09:10:09 by avieira-          #+#    #+#             */
/*   Updated: 2025/10/02 14:53:51 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_printstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_printstr_fd("(null)", fd));
	while (*str)
		i += ft_printchar_fd(*str++, fd);
	return ((i));
}
