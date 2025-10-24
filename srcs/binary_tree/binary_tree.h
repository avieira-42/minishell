#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "../parsing/parsing.h"

typedef struct s_redirect
{
	t_token_type		redir_type;
	char				*filename;
	char				*limiter;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_command
{
	t_redirect		*redirects;
	char			**argv;
}	t_command;

typedef struct s_btree
{
	t_token_type	node_type;
	t_command		*command;
	struct s_btree	*left;
	struct s_btree	*right;
}	t_btree;

t_btree	*btree_create(t_token_list *tokens);
void	btree_print(t_btree *btree, int indent, bool tree_top);

#endif
