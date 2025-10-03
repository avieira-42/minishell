#include "minishell.h"

void    minishell_loop(void)
{
    char    *user_input;

    user_input = NULL;
    while (TRUE)
    {
        user_input = readline(PROMPT_MINISHELL);
        // user_input_expand
        // tokenize command
        free(user_input);
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
