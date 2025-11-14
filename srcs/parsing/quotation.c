#include "parsing.h"

bool    is_quote_to_remove(char c, int quoted_text, char quote)
{
    if (((c == SQUOTE_LITERAL || c == DQUOTE_LITERAL)
                && quoted_text == -1)
            || (quoted_text == 1 && c == quote))
        return (true);
    return (false);
}

void    quotation_check(t_token_list *tokens)
{
    int     i;
    int     quoted;
    char    quote;

    while (tokens != NULL)
    {
        i = 0;
        quoted = -1;
        quote = '\0';
        while(tokens->token_string[i++] != '\0')
        {
            if (is_quote_to_remove(tokens->token_string[i - 1], quoted, quote))
            {
                quote = tokens->token_string[i - 1];
                quoted *= -1;
            }
        }
        if (quote != '\0' && quoted == 1)
            tokens->is_open_quoted = true;
        else if (quote != '\0' && quoted == -1)
            tokens->is_quoted = true;
        tokens = tokens->next;
    }
}

void    quoted_text_check(char c, int *quoted, char quote)
{
    if (c == quote)
        *quoted *= -1;
}

void    quote_remove(char *token)
{
    int     i;
    int     quoted_text;
    int     token_len;
    char    quote;

    i = 0;
    quoted_text = -1;
    token_len = ft_strlen(token);
    quote = '\0';
    while(token[i] != '\0')
    {
        i++;
        if (is_quote_to_remove(token[i - 1], quoted_text, quote))
        {
            quote = token[i - 1];
            ft_memmove(&token[i - 1], &token[i], token_len - (i - 1));
            i--;
            quoted_text *= -1;
        }
    }
}

void	quote_removal(t_token_list *tokens)
{
	while (tokens != NULL)
	{
		if (tokens->is_quoted == true)
			quote_remove(tokens->token_string);
		tokens = tokens->next;
	}
}
