#include "../libs/libft/include/libft.h"

#ifndef TYPES_H
#define TYPES_H

// MACROS
# define CMD "command"
# define STRING "string"
# define FILE "file"
# define BACK_SLASH '\\'
# define SPACE ' '
# define STRING_SPACE " "
# define REDIRECT_IN '<'
# define STRING_REDIRECT_IN "<"
# define REDIRECT_OUT '>'
# define STRING_REDIRECT_OUT ">"
# define HEREDOC "<<"
# define APPEND ">>"
# define PIPE '|'
# define STRING_PIPE "|"
# define LOGICAL_OR "||"
# define LOGICAL_AND "&&"
# define DQUOTE_LITERAL '\"'
# define SQUOTE_LITERAL '\''
# define EXPANSION_VARS '$'
# define EXPANSION_EXIT "?"
# define OPEN_PAREN '('
# define CLOSE_PAREN ')'
# define LVLERR "minishell: warning: shell level (%i) too high, resetting to 1\n"
# define DIR_ERR "minishell: %s: Is a directory\n"

// TOKENS
typedef enum e_token_type
{
    TOKEN_NULL,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_HEREDOC,
    TOKEN_APPEND,
    TOKEN_CMD,
    TOKEN_FILE,
    TOKEN_SPACE,
    TOKEN_COMMAND,
    TOKEN_PIPE,
    TOKEN_DQUOTE_LITERAL,
    TOKEN_SQUOTE_LITERAL,
    TOKEN_EXPANSION_VARS,
    TOKEN_EXPANSION_EXIT,
    TOKEN_LIMITER,
}   t_token_type;

extern int	g_last_signal;

typedef struct s_token_list
{
    t_token_type        token_type;
    char                *token_string;
    bool                is_quoted;
    bool                is_open_quoted;
    struct s_token_list *next;
}   t_token_list;

typedef struct s_iter
{
    int     i;
    int     j;
}   t_iter;

typedef struct s_redirect
{
	t_token_type		redir_type;
	int					fd;
	int					open_flags;
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

typedef struct s_command_get
{
	int				i;
	int				count;
	t_token_type	toktype;
	t_redirect		*node_red;
} t_command_get;

typedef struct s_shell
{
	int				argc;
	char			**argv;
	char			**envp;
	char			*user_input;
	int				exit_code;
	int				merge_ret;
	size_t			env_size;
	char			**env_vars;
	t_str_array		export_vars;
	t_token_list	*tokens;
	t_btree			*tree;
	bool			lvl_message;
}	t_shell;

#endif
