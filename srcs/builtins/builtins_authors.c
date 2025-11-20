/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_authors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:42:22 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:42:40 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/libft/include/libft.h"

void	builtins_authors_part_1(void)
{
	ft_printf("\n\n\n\n\n");
	ft_printf("╔═══ MINISHELL ");
	ft_printf("════════════════════");
	ft_printf("════════════════════");
	ft_printf("══════════╗\n");
	ft_printf("║");
	ft_printf("                                             ");
	ft_printf("     ║\n");
	ft_printf("║    Made by:");
	ft_printf("                                   ");
	ft_printf("     ║\n");
	ft_printf("║");
	ft_printf("                                             ");
	ft_printf("     ║\n");
	ft_printf("║    Julio Cesar");
	ft_printf("                 ██████     ");
	ft_printf("████████    ║\n");
	ft_printf("║    <jcesar-s@student.");
	ft_printf("42porto.com>          ");
	ft_printf("██  ███    ███     ███   ║\n");
	ft_printf("║    <https://github.com/");
	ft_printf("JulioSouza09>     ██   ");
	ft_printf("███           ████    ║\n");
}

void	builtins_authors_part_2(void)
{
	ft_printf("║");
	ft_printf("                    ██    ███      ");
	ft_printf("    ███       ║\n");
	ft_printf("║    Alexandre ");
	ft_printf("Soeiro                   ");
	ft_printf("███████████      ███          ║\n");
	ft_printf("║    <avieira-@");
	ft_printf("student.42porto.com>         ");
	ft_printf("███       ███             ║\n");
	ft_printf("║    <https://github.com/");
	ft_printf("avieira-42>       ███      ");
	ft_printf("████████████      ║\n");
	ft_printf("║");
	ft_printf("                                             ");
	ft_printf("     ║\n");
	ft_printf("╚════════════════════");
	ft_printf("════════════════════");
	ft_printf("══════════ Porto ╝\n");
	ft_printf("\n\n\n\n\n");
}

int	builtins_authors(void)
{
	builtins_authors_part_1();
	builtins_authors_part_2();
	return (0);
}
