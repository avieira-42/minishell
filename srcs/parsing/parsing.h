#ifndef PARSING_H
# define PARSING_H

#include "../../libs/libft/include/libft.h"
#include "../error/error.h"

// COMMAND
# define CMD "command"

// OPERATORS AND SPECIAL CHARACTERS
# define SPACE ' '
# define STRING_SPACE " "
# define REDIRECT_IN '<'
# define STRING_REDIRECT_IN ">"
# define REDIRECT_OUT '>'
# define STRING_REDIRECT_OUT "<"
# define HEREDOC "<<"
# define APPEND ">>"
# define PIPE '|'
# define STRING_PIPE "|"
# define LOGICAL_OR "||"
# define LOGICAL_AND "&&"
# define DQUOTE_LITERAL '\"'
# define SQUOTE_LITERAL '\''
# define EXPANSION_VARS '$'
# define EXPANSION_EXIT "?"
# define OPEN_PAREN '('
# define CLOSE_PAREN ')'

// TOKENS
typedef enum e_token_type
{
    TOKEN_NULL,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
    TOKEN_CMD,
    TOKEN_FILE,
    TOKEN_SPACE,
    TOKEN_COMMAND,
    TOKEN_PIPE,
    TOKEN_DQUOTE_LITERAL,
    TOKEN_SQUOTE_LITERAL,
    TOKEN_EXPANSION_VARS,
    TOKEN_EXPANSION_EXIT,
    TOKEN_LIMITER,
}   t_token_type;

typedef struct s_token_list
{
    t_token_type        token_type;
    char                *token_string;
    bool                is_quoted;
    bool                is_open_quoted;
    struct s_token_list *next;
}   t_token_list;

typedef struct s_iter
{
    int     i;
    int     j;
}   t_iter;

// STRING_LITERAL
# define STRING "string"

// FILE
# define FILE "file"

// CHARACTER
# define BACK_SLASH '\\'

//BOOLEAN
bool    is_operator(char *c);

// TOKEN_LIST
void	        ft_token_lst_clear(t_token_list **lst);
void	        ft_token_lst_add_back(t_token_list **lst, t_token_list *new_node);
t_token_list	*ft_token_lst_new(char *token);
t_token_list	*ft_token_lst_last(t_token_list *lst);

// TOKENIZE
void    tokenize_user_input(t_token_list **tokens, char *user_input);
void    tokenize_squoted_text(t_token_list **tokens, char *user_input, int *i);

// QUOTATION
void    quotation_check(t_token_list *tokens);
void    quoted_text_check(char c, int *quoted, char quote);
void    quote_remove(char *token);

// EXPANSION
void    token_expand(t_token_list *tokens, char **envp);

// TOKEN_IDENTIFY
void    token_identify(t_token_list *tokens);
bool    is_enum_redirect_token(t_token_type token);

//TOKEN_PARSE
int		user_input_parse(char *readline, t_token_list **tokens);

// ENVIRONMENT_VARIABLES
char	*environment_variable_get(char **envp, char *variable_name, int *j);
int     environment_variable_len(char *variable_name);
bool    is_variable(char *token_string, int i);

// TOKEN_ERROR
void	error_exit_tokens(char *user_input, t_token_list *tokens, int error_code);

#endif
