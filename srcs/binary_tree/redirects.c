#include "binary_tree.h"
#include "../cleaning/cleaning.h"

static
void	redirect_set(t_redirect *node, int fd, int open_flags)
{
	node->fd = fd;
	node->open_flags = open_flags;
}

t_redirect	*redirect_add_new(t_token_type redir_type, char *filename)
{
	t_redirect *node_new;

	node_new = malloc(sizeof(t_redirect));
	if (node_new == NULL)
		return (NULL);
	if (redir_type == TOKEN_REDIRECT_IN)
		redirect_set(node_new, STDIN_FILENO, O_RDONLY);
	else if (redir_type == TOKEN_REDIRECT_OUT)
		redirect_set(node_new, STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC);
	else if (redir_type == TOKEN_APPEND)
		redirect_set(node_new, STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND);
	else if (redir_type == TOKEN_HEREDOC)
		redirect_set(node_new, -1, 0);
	node_new->redir_type = redir_type;
	node_new->filename = filename;
	node_new->next = NULL;
	return (node_new);
}

t_redirect *redirect_last(t_redirect *redirs)
{
	while (redirs->next != NULL)
		redirs = redirs->next;
	return (redirs);
}

void	redirect_add_back(t_redirect **redirs, t_redirect *node_new)
{
	t_redirect	*node_last;

	if (*redirs == NULL)
		*redirs = node_new;
	else
	{
		node_last = redirect_last(*redirs);
		node_last->next = node_new;
	}
}

void	redirect_clear(t_redirect *redirs)
{
	t_redirect	*tmp;

	tmp = NULL;
	while (redirs != NULL)
	{
		safe_close(&redirs->fd);
		if (redirs->filename != NULL)
			free (redirs->filename);
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}
