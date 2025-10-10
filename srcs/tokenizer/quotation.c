#include "tokenizer.h"

void    quotation_check(char *quoted_text, t_token_list *token)
{
    char    quote_type;

    quote_type = *quoted_text;
    token->is_open_quoted = true;
    token->is_quoted = false;
    quoted_text++;
    while (*quoted_text != '\0' && *quoted_text != quote_type)
        quoted_text++;
    if (*quoted_text == '\0')
        return ;
    if (*quoted_text == quote_type)
    {
        token->is_open_quoted = false;
        token->is_quoted = true;
    }
    quoted_text++;
    if (*quoted_text != '\0')
        quotation_check(quoted_text, token);
}

void    quote_type_identify(t_token_list *tokens)
{
    char    *quote_ptr;

    while (tokens != NULL)
    {
        quote_ptr = ft_strchr(tokens->token_string, DQUOTE_LITERAL);
        if (quote_ptr != NULL)
            quotation_check(quote_ptr, tokens);
        else
        {
            quote_ptr = ft_strchr(tokens->token_string, SQUOTE_LITERAL);
            if (quote_ptr != NULL)
                quotation_check(quote_ptr, tokens);
        }
        tokens = tokens->next;
    }
}
