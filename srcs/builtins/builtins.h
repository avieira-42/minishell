#ifndef BUILTINS_H
# define BUILTINS_H
# define PATH_MAX 4096

int	builtins_echo(char **user_input);
int	builtins_exec(char **argv, char **envp);
int	builtins_pwd(void);
int	builtins_cd(char **argv, char **envp);
int	builtins_env(char **argv, char **envp);

#endif
