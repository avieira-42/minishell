#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "../../libs/libft/include/libft.h"

// COMMAND
# define CMD "command"

// OPERATORS AND SPECIAL CHARACTERS
# define SPACE ' '
# define REDIRECT_IN '>'
# define REDIRECT_OUT '<'
# define HEREDOC "<<"
# define APPEND ">>"
# define PIPE '|'
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
    TOKEN_SPACE,
    TOKEN_COMMAND,
    TOKEN_ARGUMENT,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
    TOKEN_PIPE,
    TOKEN_LOGICAL_OR,
    TOKEN_LOGICAL_AND,
    TOKEN_DQUOTE_LITERAL,
    TOKEN_SQUOTE_LITERAL,
    TOKEN_EXPANSION_VARS,
    TOKEN_EXPANSION_EXIT,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
}   t_token_type;

typedef struct s_token_list
{
    t_token_type        token_type;
    char                *token_string;
    bool                is_quoted;
    bool                is_open_quoted;
    struct s_token_list *next;
}   t_token_list;

// STRING_LITERAL
# define STRING "string"

// FILE
# define FILE "file"

// CHARACTER
# define BACK_SLASH '\\'


/* where the functions regarding the seperation of tokens (categories of a string) will be 
 *
 * lets look at :
 * infile < ls -l | grep -H ".h" * | vim > outfile && mkdir header_modules
 * infile = file
 * < = operator
 * ls -l = command
 * | = operator
 * grep -H = command 
 * ".h" = string
 * | = operator
 * vim = cmd */

t_token_type    token_identify(char *token);

#endif
