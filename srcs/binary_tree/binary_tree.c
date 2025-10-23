#include "binary_tree.h"

void	btree_print(t_btree *btree, int indent, bool tree_top);

void	btree_print_contents(t_btree *btree, int indent)
{
	char	*argument;

	if (btree == NULL)
		return ;
	argument = NULL;
	if (btree->node_type == TOKEN_CMD)
		argument = "CMD";
	else if (btree->node_type == TOKEN_PIPE)
		argument = "PIPE";
	printf("%*s\n", indent, argument);
}

void	btree_print(t_btree *btree, int indent, bool tree_top)
{
	int	indent_left;
	int	indent_right;
	int	space;

	space = 1;
	if (tree_top == true)
	{
		printf ("%*s\n", indent, "BINARY_TREE");
		indent = indent - 5;
		printf ("%*s\n", indent, "|");
		printf ("%*s\n", indent, "|");
		tree_top = false;
		indent_left = indent - space;
		indent_right = space * 2;
	}
	while (btree != NULL)
	{
		printf("%*s", indent_left, "/");
		printf("%*s\n", indent_right, "\\");
		indent_left = indent_left - space;
		indent_right = indent_right + space * 2;
		printf("%*s", indent_left, "/");
		printf("%*s\n", indent_right, "\\");
		indent_left = indent_left - space;
		indent_right++;
		btree_print_contents(btree->left, indent_left);
		btree_print_contents(btree->right, indent_right);
		btree = btree->left;
		printf("\n");
	}
}

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

int	command_count(t_token_list *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && tokens->token_type != TOKEN_PIPE)
	{
		if (tokens->token_type == TOKEN_CMD)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

void	command_init(int *i, int *cmd_size, t_token_list **tokens, t_btree *node)
{
	*i = 0;
	*cmd_size = command_count(*tokens);
	node->command = malloc(sizeof(t_command));
	node->command->redirects = NULL;
	// might need to set command to NULL when no commands
	node->command->argv = malloc(sizeof(char *) * (*cmd_size + 1));
	node->command->argv[*cmd_size] = NULL;
}

void	command_get(t_token_list **tokens, t_btree *node)
{
	int				i;
	int				cmd_count;
	t_token_type	token_type;
	t_redirect		*node_redir;

	token_type = TOKEN_NULL;
	command_init(&i, &cmd_count, tokens, node);
	while (*tokens != NULL && (*tokens)->token_type != TOKEN_PIPE)
	{
		token_type = (*tokens)->token_type;
		if (token_type == TOKEN_CMD)
		{
			node->command->argv[i] = (*tokens)->token_string;
			i++;
		}
		else if (is_enum_redirect_token(token_type) == true)
		{
			(*tokens) = (*tokens)->next;
			node_redir = redirect_add_new(token_type, (*tokens)->token_string);
			redirect_add_back(&(node->command->redirects), node_redir);

		}
		(*tokens) = (*tokens)->next;
	}
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

t_btree	*btree_create(t_token_list *tokens)
{
	t_btree			*btree;
	t_btree			*node_new;

	btree = NULL;
	while (tokens != NULL)
	{
		node_new = btree_add_new();
		if (tokens->token_type == TOKEN_CMD
				|| is_enum_redirect_token(tokens->token_type) == true)
		{
			node_new->node_type = TOKEN_CMD;
			command_get(&tokens, node_new);
		}
		else if (tokens->token_type == TOKEN_PIPE)
		{
			node_new->node_type = TOKEN_PIPE;
			node_new->command = NULL;
			tokens = tokens->next;
		}
		btree_add_leaf(&btree, node_new);
	}
	return (btree);
}
