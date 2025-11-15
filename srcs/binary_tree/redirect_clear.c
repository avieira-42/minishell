#include "binary_tree.h"
#include "../cleaning/cleaning.h"

void	redirect_clear_safe(t_redirect *redirs)
{
	t_redirect	*tmp;

	tmp = NULL;
	while (redirs != NULL)
	{
		if (redirs->redir_type == TOKEN_HEREDOC)
			safe_close(&(redirs->fd));
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}

void	redirect_clear(t_redirect *redirs)
{
	t_redirect	*tmp;

	tmp = NULL;
	while (redirs != NULL)
	{
		if (redirs->redir_type == TOKEN_HEREDOC)
			safe_close(&(redirs->fd));
		if (redirs->filename != NULL)
			free (redirs->filename);
		tmp = redirs->next;
		free(redirs);
		redirs = tmp;
	}
}
