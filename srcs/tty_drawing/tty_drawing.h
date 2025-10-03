#ifndef TTY_H
# define TTY_H

# include "../../libs/libft/include/libft.h"

# define CMD_AUTHORS "authors"
# define CMD_LOGO "logo"
# define FILE_AUTHORS "srcs/tty_drawing/authors.txt"
# define FILE_LOGO "srcs/tty_drawing/logo.txt"

void    draw_from_file(char *file_name);
void    special_user_input_check(char *command);

#endif
