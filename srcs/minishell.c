#include "minishell.h"

// TESTING AREA START
void    tokens_check(t_token_list *tokens, char **envp)
{
    t_token_list    *expanded_tokens;
    t_token_list    *unquoted_tokens;

    expanded_tokens = tokens;
    unquoted_tokens = tokens;

    //check token speration
    printf("\nTOKENS_CHECK\n");

    //check quotation
    printf("\nQUOTATION_CHECK\n");
    while (tokens != NULL)
    {
        printf("[%s] ", tokens->token_string);

        if (tokens->is_open_quoted == true)
            printf("open_quoted\n");
        else if (tokens->is_quoted == true)
            printf("quoted\n");
        else
            printf("unquoted\n");

        tokens = tokens->next;
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

    printf("\n");
}
// TESTING AREA END

void    minishell_loop(char **envp)
{
    char            *user_input;
    t_token_list    *tokens;

    user_input = NULL;
    tokens = NULL;
    while (TRUE)
    {
        user_input = readline(PROMPT_MINISHELL);
        if (user_input == NULL)
            break ;
        add_history(user_input);
        special_user_input_check(user_input);
        tokenize_user_input(&tokens, user_input);
        // tokenize command
        if (tokens != NULL)
            tokens_check(tokens, envp);
        free(user_input);
        if (tokens != NULL)
            ft_token_lst_clear(&tokens);
        // >> alongside builtins >> (special_user_input_check(user_input)); <<
    }
}

int main(int argc, char **argv, char **envp)
{
    (void)  argv;
    (void)  envp;

    parse_start(argc, argv[1]);
    draw_from_file(FILE_LOGO);
    minishell_loop(envp);
    clear_history();
}
