#include "tokenizer.h"
#include "../environment_variables/environment_variables.h"

void    single_quotation_skip(char *buffer, char *token_string, t_iter *iter)
{
    buffer[iter->j] = token_string[iter->i];
    (iter->i)++;
    (iter->j)++;
    while (token_string[iter->i] != SQUOTE_LITERAL && token_string[iter->i] != '\0')
    {
        buffer[iter->j] = token_string[iter->i];
        (iter->i)++;
        (iter->j)++;
    }
    buffer[iter->j] = token_string[iter->i];
    (iter->i)++;
    (iter->j)++;
}

void    expansion_vars_handle(char *buf, char *token, t_iter *iter, char **envp)
{
    char    *expansion;

    expansion = environment_variable_get(envp, &token[iter->i], &(iter->i));
    ft_memcpy(&buf[iter->j], expansion, ft_strlen(expansion));
    iter->j += ft_strlen(expansion);
}

void    token_expansion_init(t_iter *iter, char **buffer, int *double_quoted)
{
    iter->i = 0;
    iter->j = 0;
    *double_quoted = -1;
    *buffer = malloc(107374182);
}

void    single_quotation_check(char c, int *double_quoted)
{
    if (c == DQUOTE_LITERAL)
        *double_quoted *= -1;
}

void    buffer_fill(char *buffer, char *token_string, t_iter *iter)
{
    buffer[iter->j] = token_string[iter->i];
    iter->i++;
    iter->j++;
}

char    *token_expanded_create(char *token_string, char **envp)
{
    t_iter  iter;
    char    *buffer;
    int     is_double_quoted;

    token_expansion_init(&iter, &buffer, &is_double_quoted);
    if (buffer == NULL)
        return (NULL);
    while (token_string[iter.i] != '\0')
    {
        single_quotation_check(token_string[iter.i], &is_double_quoted);
        if (token_string[iter.i] == SQUOTE_LITERAL && is_double_quoted == -1)
            single_quotation_skip(buffer, token_string, &iter);
        if (is_variable(token_string, iter.i) == true)
            expansion_vars_handle(buffer, token_string, &iter, envp);
        else
            buffer_fill(buffer, token_string, &iter);
    }
    buffer[iter.j] = '\0';
    free(token_string);
    token_string = ft_strdup(buffer);
    free(buffer);
    return (token_string);
}

void    token_expand(t_token_list *tokens, char **envp)
{
    while (tokens != NULL)
    {
        tokens->token_string = token_expanded_create(tokens->token_string, envp);
        tokens = tokens->next;
    }
}
