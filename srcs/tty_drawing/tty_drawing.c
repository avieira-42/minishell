#include "tty_drawing.h"

void    draw_from_file(char *file_name)
{
    int     fd;
    char    *new_line;

    fd = open(file_name, O_RDONLY);
    while (1)
    {
        new_line = get_next_line(fd);
        if (new_line == NULL)
            break;
        ft_printf("%s", new_line);
        free (new_line);
    }
    free (new_line);
    close(fd);
}

void    special_user_input_check(char *command)
{
    if (ft_bool_strcmp(command, CMD_AUTHORS) == TRUE)
        draw_from_file(FILE_AUTHORS);
    else if (ft_bool_strcmp(command, CMD_LOGO) == TRUE)
        draw_from_file(FILE_LOGO);
}
