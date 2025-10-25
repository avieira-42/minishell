#include "binary_tree.h"
t_redirect	*redirect_add_new(t_token_type redir_type, char *filename);
void	redirect_add_back(t_redirect **redirs, t_redirect *node_new);
t_redirect *redirect_last(t_redirect *redirs);

t_redirect	*redirect_add_new(t_token_type redir_type, char *filename)
{
	t_redirect *node_new;

	node_new = malloc(sizeof(t_redirect));
	if (node_new == NULL)
		return (NULL);
	node_new->redir_type = redir_type;
	node_new->filename = filename;
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
