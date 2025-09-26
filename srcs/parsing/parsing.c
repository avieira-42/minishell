/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:15:04 by avieira-          #+#    #+#             */
/*   Updated: 2025/09/26 15:33:54 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../error/error.h"

void    parse_start(int argc, char *argv1)
{
    if (argc != 1)
        error_exit(argv1);
}
