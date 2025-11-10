#include "../parsing/parsing.h"

bool    is_variable(char *token_string, int i)
{
    if (token_string[i] != EXPANSION_VARS)
        return (false);
    i++;
    if (token_string[i] == EXPANSION_VARS)
        return (false);
    if (token_string[i] == DQUOTE_LITERAL || token_string[i] == '\0'
        || ft_isspace(token_string[i]))
        return (false);
    if (ft_isalnum(token_string[i]) == true || token_string[i] == '_')
        return (true);
    return (false);
}

inline
int     environment_variable_len(char *variable_name)
{
    int i;

    i = 0;
    if (ft_isdigit(variable_name[i]))
            return (1);
    i++;
    while (ft_isalnum(variable_name[i]) && variable_name[i] != '\0')
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
