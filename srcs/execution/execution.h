#ifndef EXECUTION_H
# define EXECUTION_H

# include "../binary_tree/binary_tree.h"

int	program_path_find(char *program_name, char **exec_paths, char **result_path);
int	command_execute(t_command *command, char **envp);

#endif
