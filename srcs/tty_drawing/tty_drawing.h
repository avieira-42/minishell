/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_drawing.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 14:24:25 by avieira-          #+#    #+#             */
/*   Updated: 2025/09/26 16:25:57 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TTY_H
# define TTY_H

# include "../../libs/libft/include/libft.h"

# define CMD_AUTHORS "authors\n"
# define CMD_LOGO "logo\n"
# define FILE_AUTHORS "srcs/tty_drawing/authors.txt"
# define FILE_LOGO "srcs/tty_drawing/logo.txt"

void    draw_from_file(char *file_name);
void    special_command_check(char *command);

#endif
