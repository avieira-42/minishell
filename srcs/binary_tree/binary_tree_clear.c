#include "binary_tree.h"

static
void	btree_node_clear(t_btree *btree_node)
{
	if (btree_node->node_type == TOKEN_PIPE)
		return ;
	else if (btree_node->node_type == TOKEN_CMD)
		if (btree_node->command != NULL)
		{
			command_clear(btree_node->command);
			btree_node->command = NULL;
		}
}

void	btree_clear(t_btree *btree_node)
{
	t_btree	*tmp;

	tmp = NULL;
	while (btree_node != NULL)
	{
		if (btree_node != NULL)
			btree_node_clear(btree_node);
		if (btree_node->right != NULL)
			btree_node_clear(btree_node->right);
		if (btree_node->left != NULL)
			btree_node_clear(btree_node->left);
		tmp = btree_node->left;
		free(btree_node);
		btree_node = tmp;
	}
}
