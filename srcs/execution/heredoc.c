#include "../minishell.h"
#include <readline/history.h>
#include "../types.h"

static
void	heredoc_write_bytes_to_file(char *line, char **envp, int fd)
{
	int		i;
	char	*expansion;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_variable(line, i))
		{
			expansion = environment_variable_get(envp, &line[i], &i);
			ft_putstr_fd(expansion, fd);
		}
		else
		{
			ft_putchar_fd(line[i], fd);
			i++;
		}
	}
	ft_putchar_fd('\n', fd);
}

static
void	heredoc_execute(char *limiter, t_redirect *redir, char **envp)
{
	char	*line;
	int		pipefd[2];

	signal(SIGINT, signal_heredoc);
	safe_pipe(pipefd);
	while (true)
	{
		if (g_last_signal == 130)
		{
			safe_close(&pipefd[0]);
			break ;
		}
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, limiter) == 0)
			break ;
		add_history(line);
		heredoc_write_bytes_to_file(line, envp, pipefd[1]);
	}
	safe_close(&pipefd[1]);
	redir->fd = pipefd[0];
}

static
void	heredoc_iterate(t_btree *node, char **envp)
{
	if (node == NULL)
		return ;
	if (node->command->redirects->redir_type == TOKEN_HEREDOC)
		heredoc_execute(
			node->command->redirects->filename,
			node->command->redirects,
			envp);
	node->command->redirects = node->command->redirects->next;
	heredoc_find(node, envp);
}

int	heredoc_find(t_btree *node, char **envp)
{
	t_redirect	*redir_save;

	if (node == NULL)
		return (-1);
	if (node->node_type == TOKEN_PIPE)
	{
		heredoc_find(node->left, envp);
		heredoc_find(node->right, envp);
	}
	else if (node->command->redirects != NULL)
	{
		redir_save = node->command->redirects;
		heredoc_iterate(node, envp);
		node->command->redirects = redir_save;
	}
	return (g_last_signal);
}
