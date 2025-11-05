#ifndef TYPES_H
#define TYPES_H

#include "parsing/parsing.h"
#include "binary_tree/binary_tree.h"

typedef struct s_shell
{
	int				argc;
	char			**argv;
	char			**envp;
	int				merge_ret;
	int				env_size;
	char			**env_vars;
	t_str_array		export_vars;
	t_token_list	*tokens;
	t_btree			*tree;
}	t_shell;


#endif
