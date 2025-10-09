#ifndef ERROR_H
# define ERROR_H

# include "../../libs/libft/include/libft.h"

# define MINI_SHELL_ERROR "minishell: "
# define NO_FILE ": No such file or directory\n"
# define CANNOT_EXECUTE ": cannot execute binary file\n"
# define IS_DIR ": Is a directory\n"

void    error_exit(char *argv1);
void    error_message_get(int error_code, char **error_message);
void    error_message_put_1(char *error_message, char *argv1);

#endif
