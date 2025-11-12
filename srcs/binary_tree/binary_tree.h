#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "../parsing/parsing.h"
# include "../types.h"

//binary_tree
void	btree_create(t_shell *shell);

//redirects
t_redirect	*
redir_add_new(t_shell *shell, t_token_type redir_type, char *filename);
t_redirect *redirect_last(t_redirect *redirs);
void	redirect_add_back(t_redirect **redirs, t_redirect *node_new);
void	redirect_clear(t_redirect *redirs);

//command
void	command_get(t_shell *shell, t_token_list **tokens, t_btree *node);
void	command_clear(t_command *command);

//binary_tree_clear
void	btree_clear(t_btree **btree);

#endif
