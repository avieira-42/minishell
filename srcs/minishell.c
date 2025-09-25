/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:28:42 by avieira-          #+#    #+#             */
/*   Updated: 2025/09/25 18:56:57 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *command;
    (void)  argc;
    (void)  argv;
    (void)  envp;

    command = NULL;
    while (1)
    {
        ft_printf("%s", "minishell ");
        command = get_next_line(STDIN_FILENO);
        if (command == NULL)
            break;
        ft_printf("%s", command);
        free(command);
    }
}
