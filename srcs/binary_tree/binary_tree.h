#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "../parsing/parsing.h"
# include "../types.h"

//binary_tree
void	btree_create(t_shell *shell);

//redirect
t_redirect	*
redir_add_new(t_shell *sh, t_token_type redir_type, char *file, t_btree **node);
t_redirect *redirect_last(t_redirect *redirs);
void	redirect_add_back(t_redirect **redirs, t_redirect *node_new);

// redirect clear
void	redirect_clear(t_redirect *redirs);
void	redirect_clear_safe(t_redirect *redirs);

//command
void	command_get(t_shell *sh, t_token_list **toks, t_btree **node);
void	command_clear(t_command *command);
void	command_clear_safe(t_command *command);
void	command_exit_clear(t_btree **tree_node);

//binary_tree_clear
void	btree_clear(t_btree **btree);
void	btree_clear_safe(t_btree **btree);

#endif
