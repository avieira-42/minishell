#include "minishell.h"

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

void    minishell_loop(void)
{
    char            *user_input;
    t_token_list    *tokens;

    user_input = NULL;
    tokens = NULL;
    while (TRUE)
    {
        user_input = readline(PROMPT_MINISHELL);
        special_user_input_check(user_input);
        tokenize_user_input(&tokens, user_input);
        if (tokens != NULL)
            tokens_check(tokens);
        // user_input_expand
        // tokenize command
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
    minishell_loop();
}
