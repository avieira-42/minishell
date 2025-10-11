#include "environment_variables.h"
#include "../tokenizer/tokenizer.h"

int     environment_variable_len(char *variable_name)
{
    int i;

    i = 0;
    while (!ft_isspace(variable_name[i])
        && variable_name[i] != '\0' && variable_name[i] != DQUOTE_LITERAL)
        i++;
    return (i);
} 

char	*environment_variable_get(char **envp, char *variable_name, int *j)
{
	int		i;
    int     variable_len;
	char	*expansion;

    (*j)++;
    variable_name++;
	i = 0;
	expansion = "";
	while (envp[i])
	{
        variable_len = environment_variable_len(variable_name);
		if (ft_bool_strncmp(envp[i], variable_name, variable_len) == true
            && envp[i][variable_len] == '=')
        {
			expansion = envp[i] + variable_len + 1;
            break;
        }
		i++;
	}
    (*j) += variable_len;
	return (expansion);
}
