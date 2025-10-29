#include "../minishell.h"
#include <unistd.h>

static
void	command_exists(t_command *command, char **command_path)
{
	char	**path_env;
	int		exit_code;

	path_env = ft_split(getenv("PATH"), ':');
	*command_path = NULL;
	exit_code = program_path_find(command->argv[0], path_env, command_path);
	free_array((void **)path_env, -1, TRUE);
	if (exit_code == ALLOC_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, ALLOC_ERROR);
		exit(EXIT_FAILURE);
	}
	else if (exit_code == NOT_FOUND_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NOT_FOUND_ERROR, command->argv[0]);
		exit(EXIT_NOT_FOUND);
	}
	else if (exit_code == NO_FILE_FAILURE)
	{
		ft_printf_fd(STDERR_FILENO, NO_FILE_ERROR, command->argv[0]);
		exit(EXIT_NOT_FOUND);
	}
}

static
void	pipe_execute(t_btree *node, int *exit_code)
{
	int	pipefd[2];
	int	pid_left;
	int	pid_right;

	pipe(pipefd);
	pid_left = pipe_child(pipefd, node->left, pipefd[1], STDOUT_FILENO);
	pid_right = pipe_child(pipefd, node->right, pipefd[0], STDIN_FILENO);
	pipe_parent(pipefd, exit_code, pid_left, pid_right);
}

static
void	heredoc_execute(char *limiter)
{
	char	*line;
	int		pipefd[2];

	pipe(pipefd);
	while (true)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
			break ;
		ft_printf_fd(pipefd[1], line);
	}
	dup2(pipefd[0], STDIN_FILENO);
	safe_close(&pipefd[1]);
	safe_close(&pipefd[0]);
}

static
void	redirect_execute(t_btree *node)
{
	int		fd;
	int		open_flags;
	char	*filename;

	fd = node->command->redirects->fd;
	open_flags = node->command->redirects->open_flags;
	filename = node->command->redirects->filename;
	if (node->command->redirects->redir_type != TOKEN_HEREDOC)
	{
		safe_close(&fd);
		if (open(filename, open_flags, 0644) < 0)
		{
			ft_printf_fd(STDERR_FILENO, "Failed to open file: %s\n", filename);
			exit(EXIT_FAILURE);
		}
	}
	else
		heredoc_execute(filename);
	node->command->redirects = node->command->redirects->next;
	traverse_btree(node);
}

static
int	command_execute(t_command *command, char **envp)
{
	char	*command_path;

	command_exists(command, &command_path);
	execve(command_path, command->argv, envp);
	perror("execve");
	exit(EXIT_FAILURE);
}

void	traverse_btree(t_btree *node)
{
	int	exit_status;

	exit_status = 0;
	if (node == NULL)
		exit(exit_status);
	if (node->node_type != TOKEN_PIPE && node->command->redirects != NULL)
		redirect_execute(node);
	if (node->node_type == TOKEN_PIPE)
		pipe_execute(node, &exit_status);
	else
		command_execute(node->command, NULL);
	exit(exit_status);
}
