#ifndef EXECUTION_H
# define EXECUTION_H
# define ALLOC_ERROR "minishell: could not allocate memory\n"
# define NOT_FOUND_ERROR "%s: command not found\n"
# define NO_FILE_ERROR "minishell: %s: No such file or directory\n"

# include "../binary_tree/binary_tree.h"

int	program_path_find(char *program_name, char **path, char **result);
int	command_execute(t_command *command, char **envp);

#endif
