#include "binary_tree.h"
#include <fcntl.h>
#include <unistd.h>

void	btree_add_to_pipe(t_btree **btree, t_btree *leaf)
{
	if (*btree == NULL)
		*btree = leaf;
	else if ((*btree)->node_type == TOKEN_PIPE)
	{
		if ((*btree)->left == NULL)
			(*btree)->left = leaf;
		else if ((*btree)->right == NULL)
			(*btree)->right = leaf;
	}
}

void	btree_add_leaf(t_btree **btree, t_btree *leaf)
{
	if (leaf->node_type == TOKEN_CMD)
	{
		btree_add_to_pipe(btree, leaf);
	}
	else if (leaf->node_type == TOKEN_PIPE)
	{
		leaf->left = *btree;
		*btree = leaf;
	}
}

t_btree	*btree_add_new(void)
{
	t_btree	*node_new;

	node_new = malloc(sizeof(t_btree));
	if (node_new == NULL)
		return (NULL);
	node_new->node_type = TOKEN_NULL;
	node_new->command = NULL;
	node_new->left = NULL;
	node_new->right = NULL;
	return (node_new);
}

t_btree	*btree_last(t_btree *btree)
{
	if (btree == NULL)
		return (NULL);
	if (btree->node_type == TOKEN_CMD)
		return (btree);
	if (btree->left == NULL)
		return (btree_last(btree->left));
	return (btree_last(btree->right));
}

void	btree_create(t_shell *shell)
{
	t_token_list	*tokens;
	t_btree			*node_new;

	tokens = shell->tokens;
	while (tokens != NULL)
	{
		node_new = btree_add_new();
		if (node_new == NULL)
			return ; // SAFE EXIT
		if (tokens->token_type == TOKEN_CMD
				|| is_enum_redirect_token(tokens->token_type) == true)
		{
			node_new->node_type = TOKEN_CMD;
			command_get(shell, &tokens, node_new);
		}
		else if (tokens->token_type == TOKEN_PIPE)
		{
			node_new->node_type = TOKEN_PIPE;
			node_new->command = NULL;
			tokens = tokens->next;
		}
		btree_add_leaf(&shell->tree, node_new);
	}
}
