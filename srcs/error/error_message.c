/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 15:17:12 by avieira-          #+#    #+#             */
/*   Updated: 2025/10/02 12:52:52 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

void error_message_put_1(char *error_message, char *argv1)
{
    ft_putstr_fd(MINI_SHELL_ERROR, 2);
    ft_putstr_fd(argv1, 2);
    ft_putstr_fd(error_message, 2);
}

void error_message_put_2(char *error_message, char *argv1)
{
    ft_putstr_fd(argv1, 2);
    ft_putstr_fd(": ", 2);
    ft_putstr_fd(argv1, 2);
    ft_putstr_fd(error_message, 2);
}

void error_message_get(int error_code, char **error_message)
{
    if (error_code == 127)
        *error_message = NO_FILE;
    else if (error_code == 126)
        *error_message = CANNOT_EXECUTE;
}
