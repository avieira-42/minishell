// TESTING AREA START
void    tokens_check(t_token_list *tokens)
{
    while (tokens != NULL)
    {
        printf("[%s] ", tokens->token_string);
        tokens = tokens->next;
    }
    printf("\n");
}
// TESTING ARE END
