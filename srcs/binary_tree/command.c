#include "binary_tree.h"
#include "../cleaning/cleaning.h"

void	command_exit_clear(t_btree **tree_node, t_command **cmd_node)
{
	if (*cmd_node != NULL)
	{
		free(*cmd_node);
		*cmd_node = NULL;
	}
	if (*tree_node != NULL)
	{
		free(*tree_node);
		*tree_node = NULL;
	}
}

void	command_clear(t_command *command)
{
	if (command->redirects != NULL)
		redirect_clear(command->redirects);
	if (command->argv != NULL)
		free_array((void **)command->argv, -1, true);
	free (command);
}

static
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

static void
command_init(t_shell *sh, t_command_get *cmd, t_token_list **tok, t_btree **node)
{
	(void)sh;

	cmd->i = 0;
	cmd->toktype = TOKEN_NULL;
	cmd->count = command_count(*tok);
	//(*node)->command = malloc(sizeof(t_command));
	(*node)->command = NULL;
	if ((*node)->command == NULL)
	{
		command_exit_clear(node, NULL);
		exit_clean(sh, 1, NULL, NULL);
	}
	(*node)->command->redirects = NULL;
	// might need to set command to NULL when no commands
	//(*node)->command->argv = malloc(sizeof(char *) * (cmd->count + 1));
	(*node)->command->argv = NULL;
	if ((*node)->command->argv == NULL)
	{
		command_exit_clear(node, &(*node)->command);
		exit_clean(sh, 1, NULL, NULL);
	}
	(*node)->command->argv[cmd->count] = NULL;
}

void	command_get(t_shell *sh, t_token_list **toks, t_btree *node)
{
	t_command_get	cmd;

	command_init(sh, &cmd, toks, &node);
	while (*toks != NULL && (*toks)->token_type != TOKEN_PIPE)
	{
		cmd.toktype = (*toks)->token_type;
		if (cmd.toktype == TOKEN_CMD)
		{
			node->command->argv[cmd.i] = (*toks)->token_string;
			cmd.i++;
		}
		else if (is_enum_redirect_token(cmd.toktype) == true)
		{
			(*toks) = (*toks)->next;
			cmd.node_red = redir_add_new(sh, cmd.toktype, (*toks)->token_string);
			cmd.node_red->next = NULL;
			redirect_add_back(&(node->command->redirects), cmd.node_red);
		}
		(*toks) = (*toks)->next;
	}
}
