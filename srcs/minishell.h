/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:50:12 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:50:14 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "../libs/libft/include/libft.h"
# include "binary_tree/binary_tree.h"
# include "parsing/parsing.h"
# include "builtins/builtins.h"
# include "execution/execution.h"
# include "cleaning/cleaning.h"
# include "types.h"

# define GREEN "\001\033[0;32m\002"
# define COLOR_RESET "\001\033[0m\002"
# define RESET   "\001\033[0m\002"

// ERROR_H
void			error_exit(char *argv1);
void			error_message_put_1(char *error_message, char *argv1);

// PARSE_H
void			parse_start(int argc, char *argv1);

// PARSER
//  token list
void			ft_token_lst_clear(t_token_list **lst);
void			ft_token_lst_add_back(t_token_list **lst,
					t_token_list *new_node);
t_token_list	*ft_token_lst_new(char *token);
t_token_list	*ft_token_lst_last(t_token_list *lst);

//token_identifiy
void			token_identify(t_token_list *tokens);

//environment_variables
char			*environment_variable_get(char **envp,
					char *variable_name, int *j);
int				environment_variable_len(char *variable_name);

// tokenize
void			tokenize_user_input(t_shell *shell);
void			tokenize_squoted_text(t_token_list **tokens,
					char *user_input, int *i);

//quotation
void			quotation_check(t_token_list *tokens);

//token_verification
int				user_input_parse(t_shell *shell);

#endif
