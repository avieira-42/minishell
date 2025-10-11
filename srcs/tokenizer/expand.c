#include "tokenizer.h"
#include "../environment_variables/environment_variables.h"

void    single_quotation_skip(char *token_string, int *i)
{
    (*i)++;
    while (token_string[*i] != SQUOTE_LITERAL && token_string[*i] != '\0')
        (*i)++;
}

char    *token_expanded_create(char *token_string, char **envp)
{
    int     i;
    int     j;
    char    *expansion;
    char    *tmp;
    char    *tmp2;

    i = 0;
    j = 0;
    while (token_string[i] != '\0')
    {
        if (token_string[i] == SQUOTE_LITERAL)
            single_quotation_skip(token_string, &i);
        if (token_string[i] == '\0')
            break;
        if (token_string[i] == EXPANSION_VARS)
        {
            j = i;
            // GIVE A NAME TO THIS FUNCTION
            expansion = environment_variable_get(envp, &token_string[i], &i);
            if (expansion == NULL)
                return (NULL);
            if (i - j == 1)
                break;
            tmp = ft_substr(token_string, 0, j);
            if (tmp == NULL)
                return (NULL);
            tmp2 = ft_strjoin(tmp, expansion);
            if (tmp2 == NULL)
                return (NULL);
            free(tmp);
            if (token_string[i] != '\0')
            {
                tmp = ft_substr(token_string, i, ft_strlen(&token_string[i]));
                if (tmp == NULL)
                    return (NULL);
            }
            free(token_string);
            token_string = ft_strjoin(tmp2, tmp);
            if (token_string == NULL)
                return (NULL);
        }
        else
            i++;
    }
    return (token_string);
}

void    token_expand(t_token_list *tokens, char **envp)
{
    while (tokens != NULL)
    {
        // DONT I HAVE TO FREE THIS BEFORE ASSIGNING TO THE NEW VALUE?
        tokens->token_string = token_expanded_create(tokens->token_string, envp);
        tokens = tokens->next;
    }
}
