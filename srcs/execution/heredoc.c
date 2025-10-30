#include "../minishell.h"

static
void	heredoc_execute(char *limiter, t_redirect *redir)
{
	char	*line;
	int		pipefd[2];

	safe_pipe(pipefd);
	while (true)
	{
		ft_printf("> ");
		line = get_next_line(STDIN_FILENO);
		if (line == NULL || ft_strncmp(line, limiter, ft_strlen(line) - 1) == 0)
			break ;
		ft_printf_fd(pipefd[1], line);
	}
	safe_close(&pipefd[1]);
	redir->fd = pipefd[0];
}

static
void	heredoc_iterate(t_btree *node)
{
	if (node == NULL)
		return ;
	if (node->command->redirects->redir_type == TOKEN_HEREDOC)
		heredoc_execute(
			node->command->redirects->filename,
			node->command->redirects);
	node->command->redirects = node->command->redirects->next;
	heredoc_find(node);
}

void	heredoc_find(t_btree *node)
{
	t_redirect	*redir_save;

	if (node == NULL)
		return ;
	if (node->node_type == TOKEN_PIPE)
	{
		heredoc_find(node->left);
		heredoc_find(node->right);
	}
	else if (node->command->redirects != NULL
		&& node->command->redirects->redir_type == TOKEN_HEREDOC)
	{
		redir_save = node->command->redirects;
		heredoc_iterate(node);
		node->command->redirects = redir_save;
	}
}
