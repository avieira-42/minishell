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
int		pipe_child(int fd[2], t_btree *node, int oldfd, int newfd, t_btree *head);
int	traverse_btree(t_btree *node);
void	pipe_parent(int fd[2], int *exit_code, int pid_left, int pid_right);
void	heredoc_find(t_btree *node, char **envp);

int		safe_fork(void);
void	safe_dup2(int oldfd, int newfd);
void	safe_pipe(int pipefd[2]);
int		*stdfd_save(void);
void	stdfd_restore(int fd[2]);

#endif
