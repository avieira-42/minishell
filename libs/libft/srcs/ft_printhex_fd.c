/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 12:25:50 by avieira-          #+#    #+#             */
/*   Updated: 2025/10/02 14:52:05 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_printhex_fd(unsigned long nbr, char c, int fd)
{
	int		count;
	int		index;
	char	*hex;

	count = 0;
	hex = "0123456789abcdef";
	if (nbr > 15)
		count += ft_printhex_fd(nbr / 16, c, fd);
	index = (nbr % 16);
	if (c == 'x')
		return (count += ft_printchar_fd(hex[index], fd));
	else
		return (count += ft_printchar_fd(ft_toupper(hex[index]), fd));
}
/*
#include <stdio.h>

int	main(void)
{
	int		nbr;

	while (1)
	{
		scanf(" %i", &nbr);
		printf("len = %i\n", printf("%x, ", nbr));
		printf(", ft_len = %i\n", ft_printhex(nbr, 'x'));
		printf("LEN = %X\n", printf("%X, ", nbr));
		printf(", FT_LEN = %i\n", ft_printhex(nbr, 'X'));
		ft_putchar('\n');
	}
}*/
