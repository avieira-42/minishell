/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:36:04 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/21 16:41:28 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../libs/libft/include/libft.h"
# include "../types.h"

//BOOLEAN
bool			is_operator(char *c);

// TOKEN_LIST
void			ft_token_lst_clear(t_token_list **lst);
void			token_lst_clear_safe(t_token_list **lst);
void			ft_token_lst_add_back(t_token_list **lst,
					t_token_list *new_node);
t_token_list	*ft_token_lst_new(char *token);
t_token_list	*ft_token_lst_last(t_token_list *lst);

// TOKENIZE
void			tokenize_user_input(t_shell *shell);
void			tokenize_squoted_text(t_token_list **tokens,
					char *user_input, int *i);
void			tokenize_dquoted_text(t_token_list **tokens,
					char *user_input, int *i);
void			tokenize_squoted_text(t_token_list **tokens,
					char *user_input, int *i);
bool			is_redirect(t_token_list *token);
void			tokenize_operator_set(t_token_list *token_node_new,
					char *c, int *i);

// QUOTATION
void			quotation_check(t_token_list *tokens);
void			quoted_text_check(char c, int *quoted, char quote);
void			quote_remove(char *token);
void			quote_removal(t_token_list *tokens);

// EXPANSION
void			token_expand(t_shell *shell);
void			single_quotation_skip(char *buffer,
					char *token_str, t_iter *iter);
void			expansion_vars_handle(char *buf, char *token,
					t_iter *iter, t_shell *shell);
void			token_expansion_init(t_iter *iter, char **buffer,
					int *double_quoted);
void			buffer_fill(char *buffer, char *token_string, t_iter *iter);
void			buffer_realloc(t_shell *sh, char *buffer,
					int j, char **token_string);

// TOKEN_IDENTIFY
void			token_identify(t_token_list *tokens);
bool			is_enum_redirect_token(t_token_type token);

//TOKEN_PARSE
int				user_input_parse(t_shell *shell);

// ENVIRONMENT_VARIABLES
char			*environment_variable_get(char **envp,
					char *variable_name, int *j);
int				environment_variable_len(char *variable_name);
bool			is_variable(char *token_string, int i);
size_t			minishell_envp_size(t_shell *shell);
int				shell_lvl_incr(t_shell *shell, char **new_var,
					char *old_var, char **tmp);
void			shell_lvl_create(t_shell *shell, char **dup);
char			**minishell_env_dup(t_shell *shell, char *lvl);

#endif
