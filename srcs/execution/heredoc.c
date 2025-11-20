#include "../minishell.h"
#include <readline/history.h>
#include "../types.h"
#include "execution.h"

static
void	heredoc_write_bytes_to_file(char *line, char **envp, int fd, bool expnd)
{
	int		i;
	char	*expansion;

	i = 0;
	while (line[i] != '\0')
	{
		if (expnd == true && is_variable(line, i))
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
void	heredoc_execute(char *limiter, t_redirect *redir, t_shell *shell)
{
	char	*line;
	int		pipefd[2];

	signal(SIGINT, signal_heredoc);
	safe_pipe(pipefd, shell);
	while (true)
	{
		if (g_last_signal == 130)
		{
			free(line);
			safe_close(&pipefd[0]);
			break ;
		}
		line = readline("> ");
		if (line == NULL || ft_strcmp(line, limiter) == 0)
			break ;
		add_history(line);
		heredoc_write_bytes_to_file(line, shell->env_vars,
			pipefd[1], redir->expand);
		free(line);
	}
	safe_close(&pipefd[1]);
	redir->fd = pipefd[0];
}

static
void	heredoc_iterate(t_btree *node, t_shell *shell)
{
	if (node == NULL)
		return ;
	if (node->command->redirects->redir_type == TOKEN_HEREDOC)
		heredoc_execute(
			node->command->redirects->filename,
			node->command->redirects,
			shell);
	node->command->redirects = node->command->redirects->next;
	heredoc_find(node, shell);
}

int	heredoc_find(t_btree *node, t_shell *shell)
{
	t_redirect	*redir_save;

	if (node == NULL)
		return (-1);
	if (node->node_type == TOKEN_PIPE)
	{
		heredoc_find(node->left, shell);
		heredoc_find(node->right, shell);
	}
	else if (node->command->redirects != NULL)
	{
		redir_save = node->command->redirects;
		heredoc_iterate(node, shell);
		node->command->redirects = redir_save;
	}
	return (g_last_signal);
}
