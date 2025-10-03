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

void    minishell_loop(void)
{
    char    *user_input;

    user_input = NULL;
    while (TRUE)
    {
        user_input = readline(PROMPT_MINISHELL);
        if (user_input == NULL)
            break;
        special_user_input_check(user_input);
        free(user_input);
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)  argv;
    (void)  envp;

    parse_start(argc, argv[1]);
    draw_from_file(FILE_LOGO);
    minishell_loop();

}
