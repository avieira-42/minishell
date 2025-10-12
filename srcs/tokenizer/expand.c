#include "tokenizer.h"
#include "../environment_variables/environment_variables.h"

void    single_quotation_skip(char *buffer, char *token_string, int *i, int *j)
{
    buffer[*j] = token_string[*i];
    (*i)++;
    (*j)++;
    while (token_string[*i] != SQUOTE_LITERAL && token_string[*i] != '\0')
    {
        buffer[*j] = token_string[*i];
        (*i)++;
        (*j)++;
    }
    buffer[*j] = token_string[*i];
    (*i)++;
    (*j)++;
}

void    buffer_expansion_fill();

char    *token_expanded_create(char *token_string, char **envp)
{
    int     i;
    int     j;
    char    *buffer;
    char    *expansion;
    int     is_double_quoted;

    i = 0;
    j = 0;
    buffer = malloc(107374182);
    if (buffer == NULL)
        return (NULL);
    is_double_quoted = -1;
    while (token_string[i] != '\0')
    {
        if (token_string[i] == DQUOTE_LITERAL)
            is_double_quoted *= -1;
        if (token_string[i] == SQUOTE_LITERAL && is_double_quoted == -1)
            single_quotation_skip(buffer, token_string, &i, &j);
        /*else if (token_string[i] == EXPANSION_VARS && token_string[i] == EXPANSION_VARS)*/
        else if (token_string[i] == EXPANSION_VARS)
        {
            /*if (token_string[i + 1] == EXPANSION_VARS)
                expansion*/
            expansion = environment_variable_get(envp, &token_string[i], &i);
            ft_memcpy(&buffer[j], expansion, ft_strlen(expansion));
            j+= ft_strlen(expansion);
        }
        else
        {
            buffer[j] = token_string[i];
            i++;
            j++;
        }
    }
    buffer[j] = '\0';
    free(token_string);
    token_string = ft_strdup(buffer);
    free(buffer);
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
