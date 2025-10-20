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

char	**command_get(t_token_list **tokens)
{
	int		i;
	char	**command;

	i = 0;
	command = malloc(sizeof(char *) * (command_count(*tokens) + 1));
	while (*tokens != NULL && (*tokens)->token_type != TOKEN_PIPE)
	{
		if (is_enum_redirect_token((*tokens)->token_type) != false)
			command[i] = (*tokens)->token_string;
		i++;
		(*tokens) = (*tokens)->next;
	}
	return (command);
}

void	btree_create(t_token_list *tokens)
{
	t_command		**command_node;
	t_token_type	token_type;
	t_btree			*b_tree;
	t_btree			*node_new;

	b_tree = NULL;
	while (tokens != NULL)
	{
		node_new = btree_add_new();
		command_node = NULL;
		if (tokens->token_type == TOKEN_CMD)
			node_new->command = command_get(&tokens);
		else if (tokens->token_type == TOKEN_PIPE)
			command = NULL;
		tokens = tokens->next;
	}
}
