#ifndef EXECUTION_H
# define EXECUTION_H

# define ALLOC_ERROR "minishell: could not allocate memory\n"
# define NOT_FOUND_ERROR "%s: command not found\n"
# define NO_FILE_ERROR "minishell: %s: No such file or directory\n"
# define EXIT_NOT_FOUND 127

# include "../types.h"

enum e_path_error
{
	ALLOC_FAILURE = -1,
	NOT_FOUND_FAILURE = 0,
	NO_FILE_FAILURE = 2,
};

int		command_exists(t_command *command, char **command_path, char **envp);
int		pipe_child(t_pipe_args *args);
int		traverse_btree(t_btree *node, t_shell *shell);
void	pipe_parent(int fd[2], int *exit_code, int pid_left, int pid_right);
int		heredoc_find(t_btree *node, char **envp);

int		safe_fork(void);
void	safe_dup2(int oldfd, int newfd);
void	safe_pipe(int pipefd[2]);
int		*stdfd_save(void);
void	stdfd_restore(int fd[2]);

int		ft_wait(int pid);
char	*env_get(char *var_name, char **envp);

void	signal_prompt(int signal);
void	signal_heredoc(int signal);
void	signal_broken_pipe(int signal);

int		redirect_open(int *fd, int open_flags, char *filename);
void	heredoc_open(int *ptr_fd);
int		ft_wait(int pid);
int		is_directory(char *cmd_name, int true_dir, int print_error);

#endif
