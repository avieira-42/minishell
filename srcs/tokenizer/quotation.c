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
    while (*quoted_text != DQUOTE_LITERAL && *quoted_text != SQUOTE_LITERAL
        && *quoted_text != '\0')
        quoted_text++;
    if (*quoted_text == DQUOTE_LITERAL || *quoted_text == SQUOTE_LITERAL)
        quotation_check(quoted_text, token);
}

void    is_single_quoted(char c, int *double_quoted)
{
    if (c == DQUOTE_LITERAL)
        *double_quoted *= -1;
}

void    is_quoted_text(char c, int *quoted, char *quote)
{
    if (c == *quote)
    {
        *quoted *= -1;
        *quote = '0';
    }
    else if (*quote == '0' && (c == DQUOTE_LITERAL || c == SQUOTE_LITERAL))
    {
        *quoted *= -1;
        *quote = c;
    }
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

void    quote_remove(char *token_string)
{
    int     i;
    int     quoted_text;
    int     token_string_len;
    char    quote;

    i = 0;
    quote = '0';
    quoted_text = -1;
    token_string_len = ft_strlen(token_string);
    while(token_string[i] != '\0')
    {
        is_quoted_text(token_string[i], &quoted_text, &quote);
        i++;
        if (quoted_tex == -1 &&)
        {
            ft_memmove(&token_string[], token_string, token_string_len - i);
        }
    }
}
