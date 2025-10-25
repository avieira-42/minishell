#include "binary_tree.h"

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
