#include "error.h"

void	error_message_put_1(char *error_message, char *argv1)
{
	ft_printf_fd(2, "%s%s%s", MINI_SHELL_ERROR, argv1, error_message);
}

void	error_message_put_2(char *error_message, char *argv1)
{
	ft_printf_fd(2, "%s: %s%s", argv1, argv1, error_message);
}

void	error_message_put_tokens(char *error_message)
{
	ft_printf_fd(2, "%s", error_message);
}

void error_message_get(int error_code, char **error_message)
{
    if (error_code == 127)
        *error_message = NO_FILE;
    else if (error_code == 126)
        *error_message = CANNOT_EXECUTE;
}
