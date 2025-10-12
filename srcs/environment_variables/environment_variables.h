#ifndef ENVIRONMENT_VARIABLES_H
# define ENVIRONMENT_VARIABLES_H

#include "../../libs/libft/include/libft.h"
#include "../error/error.h"

char	*environment_variable_get(char **envp, char *variable_name, int *j);
int     environment_variable_len(char *variable_name);
bool    is_variable(char *token_string, int i);

#endif
