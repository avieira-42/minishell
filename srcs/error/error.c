#include "error.h"

static void error_code_get(char *argv1, int *error_code)
{
    (void) argv1;
    // need to find a way to get the right exit_code
    *error_code = 127;
}

void error_exit_argv(char *argv1)
{
    int     error_code;
    char    *error_message;

    error_code_get(argv1, &error_code);
    error_message_get(error_code, &error_message);
    error_message_put_1(error_message, argv1);
    exit (error_code);
}
