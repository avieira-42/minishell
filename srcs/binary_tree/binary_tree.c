#include "binary_tree.h"

t_btree	*btree_add_new(void)
{
	t_btree	*node_new;

	node_new = malloc(sizeof(t_btree));
	if (node_new == NULL)
		return (NULL);
	node_new->node_type = TOKEN_NULL;
	node_new->left = NULL;
	node_new->right = NULL;
	return (node_new);
}

int	command_count(t_token_list *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && tokens->token_type != TOKEN_PIPE)
	{
		if (is_enum_redirect_token(tokens->token_type) != false)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	command_init(t_token_list **tokens, t_btree *node)
{
	// NEED TO INITIALIZE REDIT_TYPE AND REDIT_COUNT
	// NEED TO RETHINK THIS WITH JULIO
	int		i;
	char	**command;

	i = 0;
	command = malloc(sizeof(char *) * (command_count(*tokens) + 1));
	if (command == NULL)
		exit(1);
	while (*tokens != NULL && (*tokens)->token_type != TOKEN_PIPE)
	{
		if (is_enum_redirect_token((*tokens)->token_type) != false)
			command[i] = (*tokens)->token_string;
		i++;
		(*tokens) = (*tokens)->next;
	}
	node->command->argv = command;
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

void	btree_add_back(t_btree *btree, t_btree node_new)
{
	t_btree	*node_last;

	node_last = btree_last(btree);
}

void	btree_create(t_token_list *tokens)
{
	t_btree			*btree;
	t_btree			*node_new;
	t_btree			*node_last;

	btree = NULL;
	while (tokens != NULL)
	{
		node_new = btree_add_new();
		if (tokens->token_type == TOKEN_CMD)
		{
			node_new->node_type = TOKEN_CMD;
			command_init(&tokens, node_new);
		}
		else if (tokens->token_type == TOKEN_PIPE)
		{
			node_new->node_type = TOKEN_PIPE;
			node_new->command = NULL;
		}
		btree_add_back(btree, node_new);
		tokens = tokens->next;
	}
}
