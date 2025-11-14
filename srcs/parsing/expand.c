#include "parsing.h"
#include "../cleaning/cleaning.h"

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

void
expansion_vars_handle(char *buf, char *token, t_iter *iter, t_shell *shell)
{
    char    *exp;

	if (ft_bool_strncmp(&token[iter->i], "$?", 2) == true)
	{
		exp = ft_itoa(shell->exit_code);
		if (exp == NULL)
			exit_clean(shell, 1, NULL, buf);
		iter->i += 2;
		ft_memcpy(&buf[iter->j], exp, ft_strlen(exp));
		iter->j += ft_strlen(exp);
		free(exp);
	}
	else
	{
		exp = environment_variable_get(shell->env_vars, &token[iter->i], &(iter->i));
		ft_memcpy(&buf[iter->j], exp, ft_strlen(exp));
		iter->j += ft_strlen(exp);
	}
}

void    token_expansion_init(t_iter *iter, char **buffer, int *double_quoted)
{
	iter->i = 0;
	iter->j = 0;
	*double_quoted = -1;
	*buffer = malloc(107374182);
}

void    buffer_fill(char *buffer, char *token_string, t_iter *iter)
{
	buffer[iter->j] = token_string[iter->i];
	iter->i++;
	iter->j++;
}

void	token_expansion_create(char **token_string, t_shell *shell)
{ 
	t_iter  iter;
	char    *buffer;
	int     is_dquote;

	token_expansion_init(&iter, &buffer, &is_dquote);
	if (buffer == NULL)
		exit_clean(shell, 1, NULL, NULL);
	while ((*token_string)[iter.i] != '\0')
	{
		quoted_text_check((*token_string)[iter.i], &is_dquote, DQUOTE_LITERAL);
		if ((*token_string)[iter.i] == SQUOTE_LITERAL && is_dquote == -1)
			single_quotation_skip(buffer, *token_string, &iter);
		else if (is_variable(*token_string, iter.i) == true)
			expansion_vars_handle(buffer, *token_string, &iter, shell);
		else
			buffer_fill(buffer, *token_string, &iter);
	}
	buffer[iter.j] = '\0';
	free(*token_string);
	*token_string = ft_strdup(buffer);
	if (*token_string == NULL)
		exit_clean(shell, 1, NULL, buffer);
	free(buffer);
}

void    token_expand(t_shell *sh)
{
	t_token_list	*tokens;

	tokens = sh->tokens;
	while (tokens != NULL)
	{
		token_expansion_create(&tokens->token_string, sh);
		tokens = tokens->next;
	}
}
