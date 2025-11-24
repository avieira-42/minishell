/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_logo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:42:47 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/24 13:55:38 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/include/libft.h"

void	builtins_logo_part_1(void)
{
	ft_printf("\n\n\n\n\n");
	ft_printf("███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗");
	ft_printf("██╗     ██╗     \n");
	ft_printf("████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝");
	ft_printf("██║     ██║     \n");
	ft_printf("██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ");
	ft_printf("██║     ██║     \n");
	ft_printf("██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ");
	ft_printf("██║     ██║     \n");
	ft_printf("██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗");
	ft_printf("███████╗███████╗\n");
}

void	builtins_logo_part_2(void)
{
	ft_printf("╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝");
	ft_printf("╚══════╝╚══════╝\n\n");
	ft_printf("A shell project created by Julio Cesar and Alexandre Soeiro at");
	ft_printf(" 42_Porto\n\n");
	ft_printf("Type:  ");
	ft_printf("\n");
	ft_printf("       authors   for more info about the awesome ");
	ft_printf("creators\n\n");
	ft_printf("       logo      to see this cool ");
	ft_printf("logo again\n\n");
	ft_printf("\n\n\n\n\n");
}

int	builtins_logo(void)
{
	builtins_logo_part_1();
	builtins_logo_part_2();
	return (0);
}
