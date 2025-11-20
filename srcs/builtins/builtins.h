/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:42:03 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/20 21:42:14 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define PATH_MAX 4096

# include "../../libs/libft/include/libft.h"
# include "../types.h"
# include "../parsing/parsing.h"

# define EXPORT_ERROR "minishell: export: '%s': not a valid identifier\n"

typedef unsigned char	t_byte;

int		builtins_echo(char **user_input);
int		builtins_exec(char **argv, char **envp, t_shell *shell);
int		builtins_pwd(void);
int		builtins_env(char **argv, char **envp);
int		builtins_exit(char **argv, t_shell *shell);
int		builtins_cd(char **argv, char **envp, t_shell *shell);
int		builtins_export(t_shell *shell, char **argv);
int		builtins_export_addvar(t_shell *shell, char *var,
			char *argv, char *end);
int		builtins_unset(t_shell *shell, char **vars);
int		builtins_authors(void);
int		builtins_logo(void);

#endif
