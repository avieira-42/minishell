#include "../minishell.h"

int echo(char *input)
{
    ft_printf(input);
    if (flag == 'n')
        ft_printf("\n");
    return (0);
}