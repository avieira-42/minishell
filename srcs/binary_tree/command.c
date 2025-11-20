/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:37:05 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/20 19:39:39 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "binary_tree.h"
#include "../cleaning/cleaning.h"

static
int	command_count(t_token_list *tokens)
{
	int	count;

	count = 0;
	while (tokens != NULL && tokens->token_type != TOKEN_PIPE)
	{
		if (tokens->token_type == TOKEN_CMD)
		{
			if (tokens->is_var == true && tokens->token_string[0] == '\0'
				&& tokens->is_quoted == false)
			{
				tokens = tokens->next;
				continue ;
			}
			else
				count++;
		}
		tokens = tokens->next;
	}
	return (count);
}

static void
	command_init(t_shell *sh, t_command_get *cmd,
			t_token_list **tok, t_btree **node)
{
	cmd->i = 0;
	cmd->toktype = TOKEN_NULL;
	cmd->count = command_count(*tok);
	(*node)->command = malloc(sizeof(t_command));
	if ((*node)->command == NULL)
	{
		command_exit_clear(node);
		exit_clean(sh, 66, NULL, NULL);
	}
	(*node)->command->redirects = NULL;
	(*node)->command->argv = malloc(sizeof(char *) * (cmd->count + 1));
	if ((*node)->command->argv == NULL)
	{
		command_exit_clear(node);
		exit_clean(sh, 66, NULL, NULL);
	}
	(*node)->command->argv[cmd->count] = NULL;
}

static
bool	command_arg_validate(t_token_list	*token)
{
	if (token->token_string[0] == '\0' && token->is_var == true
		&& token->is_quoted == false)
	{
		free(token->token_string);
		return (true);
	}
	return (false);
}

static
void	command_redirect(t_shell *sh, t_token_list **toks,
			t_command_get cmd, t_btree **node)
{
	t_token_type	redir_type;

	redir_type = (*toks)->token_type;
	(*toks) = (*toks)->next;
	cmd.node_red = redir_add_new(sh, cmd.toktype,
			(*toks)->token_string, node);
	if (redir_type == TOKEN_HEREDOC && (*toks)->is_quoted)
		cmd.node_red->expand = false;
	cmd.node_red->next = NULL;
	redirect_add_back(&((*node)->command->redirects), cmd.node_red);
}

void	command_get(t_shell *sh, t_token_list **toks, t_btree **node)
{
	t_command_get	cmd;
	bool			should_skip;

	command_init(sh, &cmd, toks, node);
	while (*toks != NULL && (*toks)->token_type != TOKEN_PIPE)
	{
		cmd.toktype = (*toks)->token_type;
		should_skip = command_arg_validate((*toks));
		if (cmd.toktype == TOKEN_CMD && should_skip == false)
		{
			(*node)->command->argv[cmd.i] = (*toks)->token_string;
			cmd.i++;
		}
		else if (is_enum_redirect_token(cmd.toktype) == true)
			command_redirect(sh, toks, cmd, node);
		(*toks) = (*toks)->next;
	}
}
