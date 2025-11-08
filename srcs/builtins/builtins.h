#ifndef BUILTINS_H
# define BUILTINS_H

int	builtins_echo(char **user_input);
int	builtins_exec(char **argv);
int	builtins_pwd(void);
int	builtins_env(char **argv, char **envp);
void	builtins_exit(char **argv);

#endif
