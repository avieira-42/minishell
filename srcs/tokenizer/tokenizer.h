/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 17:38:29 by avieira-          #+#    #+#             */
/*   Updated: 2025/10/17 17:48:50 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include "../../libs/libft/include/libft.h"
#include "../environment_variables/environment_variables.h"

// COMMAND
# define CMD "command"

// OPERATORS AND SPECIAL CHARACTERS
# define SPACE ' '
# define STRING_SPACE " "
# define REDIRECT_IN '>'
# define STRING_REDIRECT_IN ">"
# define REDIRECT_OUT '<'
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

#endif
