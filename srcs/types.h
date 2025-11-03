#ifndef TYPES_H
#define TYPES_H

#include "parsing/parsing.h"
#include "binary_tree/binary_tree.h"

typedef struct s_shell
{
	int				argc;
	int				level;
	char			**envp;
	char			**env_vars;
	char			**export_vars;
	char			**argv;
	t_token_list	*tokens;
	t_btree			*tree;
}	t_shell;


#endif
