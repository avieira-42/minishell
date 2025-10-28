#ifndef EXECUTION_H
# define EXECUTION_H
# define ALLOC_ERROR "minishell: could not allocate memory\n"
# define NOT_FOUND_ERROR "%s: command not found\n"
# define NO_FILE_ERROR "minishell: %s: No such file or directory\n"
# define EXIT_NOT_FOUND 127

# include "../binary_tree/binary_tree.h"

enum e_path_error
{
	ALLOC_FAILURE = -1,
	NOT_FOUND_FAILURE = 0,
	NO_FILE_FAILURE = 2,
};

int		program_path_find(char *program_name, char **path, char **result);
void	traverse_btree(t_btree *node);
void	pipe_parent(int fd[2], int *exit_code, int pid_left, int pid_right);
int		pipe_child(int fd[2], t_btree *node, int oldfd, int newfd);

#endif
