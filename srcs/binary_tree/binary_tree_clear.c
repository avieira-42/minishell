#include "binary_tree.h"

static
void	btree_node_clear_safe(t_btree *btree_node)
{
	if (btree_node->node_type == TOKEN_PIPE)
		return ;
	else if (btree_node->node_type == TOKEN_CMD)
	{
		if (btree_node->command != NULL)
		{
			command_clear_safe(btree_node->command);
			btree_node->command = NULL;
		}
	}
}

void	btree_clear_safe(t_btree **btree)
{
	t_btree	*tmp;
	t_btree	*btree_node;

	tmp = NULL;
	btree_node = *btree;
	while (btree_node != NULL)
	{
		if (btree_node != NULL)
			btree_node_clear_safe(btree_node);
		if (btree_node->right != NULL)
		{
			btree_node_clear_safe(btree_node->right);
			free(btree_node->right);
		}
		if (btree_node->left != NULL)
			btree_node_clear_safe(btree_node->left);
		tmp = btree_node->left;
		free(btree_node);
		btree_node = tmp;
	}
	*btree = NULL;
}

static
void	btree_node_clear(t_btree *btree_node)
{
	if (btree_node->node_type == TOKEN_PIPE)
		return ;
	else if (btree_node->node_type == TOKEN_CMD)
	{
		if (btree_node->command != NULL)
		{
			command_clear(btree_node->command);
			btree_node->command = NULL;
		}
	}
}

void	btree_clear(t_btree **btree)
{
	t_btree	*tmp;
	t_btree	*btree_node;

	tmp = NULL;
	btree_node = *btree;
	while (btree_node != NULL)
	{
		if (btree_node != NULL)
			btree_node_clear(btree_node);
		if (btree_node->right != NULL)
		{
			btree_node_clear(btree_node->right);
			free(btree_node->right);
		}
		if (btree_node->left != NULL)
			btree_node_clear(btree_node->left);
		tmp = btree_node->left;
		free(btree_node);
		btree_node = tmp;
	}
	*btree = NULL;
}
