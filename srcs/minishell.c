#include "minishell.h"

// TESTING AREA START
void    tokens_check(t_token_list *tokens, char **envp, char *user_input)
{
    t_token_list    *quotation_tokens;
    t_token_list    *expanded_tokens;
    t_token_list    *unquoted_tokens;
    t_token_list    *identified_tokens;
    t_token_list    *unidentified_tokens;
    char            *token_type;


    //check token speration
    printf("\nTOKENS_CHECK\n");
    tokenize_user_input(&tokens, user_input);
    quotation_tokens = tokens;
    expanded_tokens = tokens;
    unquoted_tokens = tokens;
    identified_tokens = tokens;
    unidentified_tokens = tokens;
    while (tokens != NULL)
    {
        printf("[%s] ", tokens->token_string);
        tokens = tokens->next;
        if (tokens == NULL)
            printf("\n");
    }

    //check quotation
    printf("\nQUOTATION_CHECK\n");
    quotation_check(quotation_tokens);
    while (quotation_tokens != NULL)
    {
        printf("[%s] ", quotation_tokens->token_string);

        if (quotation_tokens->is_open_quoted == true)
            printf("open_quoted\n");
        else if (quotation_tokens->is_quoted == true)
            printf("quoted\n");
        else
            printf("unquoted\n");

        quotation_tokens = quotation_tokens->next;
    }

    // check expansion
    printf("\nEXPANSION_CHECK\n");
    token_expand(expanded_tokens, envp);
    while (expanded_tokens != NULL)
    {
        printf("[%s]\n", expanded_tokens->token_string);
        expanded_tokens = expanded_tokens->next;
    }

    // quote remove
    printf("\nQUOTATION_REMOVE_CHECK\n");
    while (unquoted_tokens != NULL)
    {
        if (unquoted_tokens->is_quoted == true)
            quote_remove(unquoted_tokens->token_string);
        printf("[%s]\n", unquoted_tokens->token_string);
        unquoted_tokens = unquoted_tokens->next;
    }

    //token_identify
    printf("\nTOKEN_IDENTIFY\n");
    while (unidentified_tokens != NULL)
    {
        printf("[%s] ", unidentified_tokens->token_string);
        unidentified_tokens = unidentified_tokens->next;
        if (unidentified_tokens == NULL)
            printf("\n");
    }

    token_identify(identified_tokens);
    while (identified_tokens != NULL)
    {
        if (identified_tokens->token_type == TOKEN_CMD)
            token_type = "COMMAND";
        else if (identified_tokens->token_type == TOKEN_REDIRECT_IN
                || identified_tokens->token_type == TOKEN_REDIRECT_OUT
                || identified_tokens->token_type == TOKEN_APPEND
                || identified_tokens->token_type == TOKEN_HEREDOC)
            token_type = "REDIRECT";
        else if (identified_tokens->token_type == TOKEN_PIPE)
            token_type = "PIPE";
        else if (identified_tokens->token_type == TOKEN_FILE)
            token_type = "FILE";
        printf("[%s] -> %s\n", identified_tokens->token_string, token_type);
        identified_tokens = identified_tokens->next;
    }

    printf("\n");
}
// TESTING AREA END

void    minishell_loop(char **envp)
{
    char *user_input;
    t_token_list *tokens;

    user_input = NULL;
    tokens = NULL;
    while (TRUE)
    {
        user_input = readline(PROMPT_MINISHELL);
        if (user_input == NULL)
            break ;
        char **test = ft_split(user_input, ' ');
        builtins_exec(test);
        add_history(user_input);
        special_user_input_check(user_input);
        // tokenize command
        tokens_check(tokens, envp, user_input);
        free(user_input);
        if (tokens != NULL)
            ft_token_lst_clear(&tokens);
        // >> alongside builtins >> (special_user_input_check(user_input)); <<
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)argv;
    (void)envp;

    parse_start(argc, argv[1]);
    draw_from_file(FILE_LOGO);
    minishell_loop(envp);
    clear_history();
}
