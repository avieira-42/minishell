/* ****************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:28:42 by avieira-          #+#    #+#             */
/*   Updated: 2025/09/26 14:03:56 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *command;
    (void)  argv;
    (void)  envp;

    parse_start(argc, argv[1]);
    draw_from_file(FILE_LOGO);
    command = NULL;
    while (TRUE)
    {
        ft_printf("%s", "minishell ");
        command = get_next_line(STDIN_FILENO);
        if (command == NULL)
            break;
        ft_printf("%s", command);
        special_command_check(command);
        free(command);
    }
}
