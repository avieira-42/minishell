#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "binary_tree/binary_tree.h"
# include "tokenizer/tokenizer.h"
# include "parsing/parsing.h"
# include "tty_drawing/tty_drawing.h"
# include "error/error.h"
# include "environment_variables/environment_variables.h"
# include "builtins/builtins.h"

# define COLOR_GREEN "\e[0;32m"
# define COLOR_RESET "\e[0m"
# define PROMPT_MINISHELL COLOR_GREEN "minishell" COLOR_RESET "$> "

// ERROR_H
void error_exit(char *argv1);
void error_message_get(int error_code, char **error_message);
void error_message_put_1(char *error_message, char *argv1);

// PARSE_H
void parse_start(int argc, char *argv1);

// PARSER
//  token list
void ft_token_lst_clear(t_token_list **lst);
void ft_token_lst_add_back(t_token_list **lst, t_token_list *new_node);
t_token_list *ft_token_lst_new(char *token);
t_token_list *ft_token_lst_last(t_token_list *lst);

//token_identifiy.h
void    token_identify(t_token_list *tokens);

// tokenize
void tokenize_user_input(t_token_list **tokens, char *user_input);
void tokenize_squoted_text(t_token_list **tokens, char *user_input, int *i);

//quotation
void    quotation_check(t_token_list *tokens);

//TTY_DRAWING_H
void    draw_from_file(char *file_name);
void    special_user_input_check(char *command);

//ENVIRONMENT_VARIABLES
char	*environment_variable_get(char **envp, char *variable_name, int *j);
int     environment_variable_len(char *variable_name);

//BINARY_TREE
t_btree	*btree_create(t_token_list *tokens);

#endif
