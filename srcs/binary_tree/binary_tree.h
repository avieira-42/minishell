#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "../tokenizer/tokenizer.h"

typedef struct s_redirect
{
	t_token_type		redir_type;
	char				*filename;
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

#endif
