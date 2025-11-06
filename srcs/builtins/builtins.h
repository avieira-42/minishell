#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../libs/libft/include/libft.h"
# include "../types.h"
# include "../parsing/parsing.h"

# define EXPORT_ERROR "minishell: export: '%s': not a valid identifier"

int		builtins_echo(char **user_input);
int		builtins_exec(char **argv);
int		builtins_pwd(void);
int		builtins_env(char **argv, char **envp);
void	builtins_export(t_shell *shell, char **argv);

#endif
