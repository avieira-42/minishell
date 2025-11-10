#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "../parsing/parsing.h"
# include "../types.h"

//binary_tree
t_btree	*btree_create(t_token_list *tokens);
void	btree_clear(t_btree *btree_node);

//redirects
t_redirect	*redirect_add_new(t_token_type redir_type, char *filename);
t_redirect *redirect_last(t_redirect *redirs);
void	redirect_add_back(t_redirect **redirs, t_redirect *node_new);
void	redirect_clear(t_redirect *redirs);

//command
void	command_get(t_token_list **tokens, t_btree *node);
void	command_clear(t_command *command);

//binary_tree_clear
void	btree_clear(t_btree *btree);

#endif
