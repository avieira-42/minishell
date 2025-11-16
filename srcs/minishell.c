#include "minishell.h"
#include "execution/execution.h"
#include <readline/readline.h>
#include <unistd.h>
#include "types.h"

int	g_last_signal;

// TESTING AREA START
void	btree_print(t_btree *btree, int indent, bool tree_top, int cmd_count);

int	btree_node_count(t_btree *btree)
{
	int	count;

	count = 1;
	while (btree != NULL)
	{
		if (btree->right)
			count++;
		if (btree->left)
			count ++;
		btree = btree->left;
	}
	return (count);
}

int	btree_cmd_count(t_btree *btree)
{
	int	count;

	count = 0;
	while (btree != NULL)
	{
		if (btree->right && btree->right->node_type == TOKEN_CMD)
			count++;
		if (btree->right && btree->left->node_type == TOKEN_CMD)
			count++;
		btree = btree->left;
	}
	return (count);
}

void	btree_print_contents(t_btree *btree, int indent, int *cmd_count)
{
	if (btree == NULL)
		return ;
	if (btree->node_type == TOKEN_CMD)
	{
		printf("%*s%i", indent, "CMD", *cmd_count);
		(*cmd_count)--;
	}
	else if (btree->node_type == TOKEN_PIPE)
		printf("%*s", indent, "PIPE");
}

void	contents_print(t_btree *btree_node, int *i, int *j)
{
	int	m;
	t_redirect	*redirects = NULL;

	m = 0;
	if (btree_node == NULL)
		return ;
	if (btree_node->command)
		redirects = btree_node->command->redirects;
	if (btree_node->node_type == TOKEN_PIPE)
	{
		printf("NODE %i -> PIPE\n", *j);
		(*j)--;
	}
	else if (btree_node->node_type == TOKEN_CMD)
	{
		printf("NODE %i -> CMD\nargv: ", *i);
		(*i)--;
		while (btree_node->command->argv[m] != NULL)
		{
			printf("%s ", btree_node->command->argv[m]);
			m++;
		}
		printf("\nredirect list: ");
		while (redirects != NULL)
		{
			if (redirects->redir_type == TOKEN_APPEND)
				printf(">> %s ", redirects->filename);
			if (redirects->redir_type == TOKEN_HEREDOC)
				printf("<< %s ", btree_node->command->redirects->filename);
			if (redirects->redir_type == TOKEN_REDIRECT_IN)
				printf("> %s ", btree_node->command->redirects->filename);
			if (redirects->redir_type == TOKEN_REDIRECT_OUT)
				printf("< %s ", btree_node->command->redirects->filename);
			redirects = redirects->next;
		}
		printf("\n\n");
	}
}

void	btree_contents_print(t_btree *btree, int node_count, int cmd_count)
{
	while (btree != NULL)
	{
		contents_print(btree->left, &cmd_count, &node_count);
		contents_print(btree->right, &cmd_count, &node_count);
		btree = btree->left;
		printf("\n");
	}
}

void	btree_print(t_btree *btree, int indent, bool tree_top, int cmd_count)
{
	int	i;
	int	space;
	int	indent_left;
	int	indent_right;

	space = 1;
	if (tree_top == true)
	{
		tree_top = false;
		printf ("%*s\n", indent, "BINARY_TREE");
		indent = indent - 5;
		printf ("%*s\n", indent, "|");
		printf ("%*s\n", indent, "|");
		btree_print_contents(btree, indent + space, &cmd_count);
		indent_left = indent - space;
		indent_right = space * 2;
		printf("\n");
	}
	i = 0;
	while (btree != NULL)
	{
		if (i > 0)
			indent_right = indent_right + 1;
		printf("%*s", indent_left, "/");
		printf("%*s\n", indent_right, "\\");
		indent_left = indent_left - space;
		indent_right = indent_right + space * 2;
		printf("%*s", indent_left, "/");
		printf("%*s\n", indent_right, "\\");
		btree_print_contents(btree->left, indent_left, &cmd_count);
		btree_print_contents(btree->right, indent_right + space * 2, &cmd_count);
		btree = btree->left;
		indent_left = indent_left - space;
		indent_right = 0;
		printf("\n");
		i++;
	}
}

void
tokens_check(t_shell *shell)
{
	char            *token_type;
	t_token_list	*tokens;
    t_token_list    *quotation_tokens;
    t_token_list    *expanded_tokens;
    t_token_list    *unquoted_tokens;
    t_token_list    *identified_tokens;
    t_token_list    *unidentified_tokens;
	t_btree			*tree;
	int				node_count;
	int				cmd_count;


    //check token speration
    printf("\nTOKENS_CHECK\n");
    tokenize_user_input(shell);
	tokens = shell->tokens;
    quotation_tokens = shell->tokens;
    expanded_tokens = shell->tokens;
    unquoted_tokens = shell->tokens;
    identified_tokens = shell->tokens;
    unidentified_tokens = shell->tokens;
    while (tokens != NULL)
    {
        printf("[%s] ", tokens->token_string);
        tokens = tokens->next;
        if (tokens == NULL)
            printf("\n");
    }

    //token_identify
    printf("\nTOKEN_IDENTIFY\n");
    while (unidentified_tokens != NULL)
    {
        printf("[%s] ", unidentified_tokens->token_string);
        unidentified_tokens = unidentified_tokens->next;
        if (unidentified_tokens == NULL)
            printf("\n");
    }

    token_identify(identified_tokens);
    while (identified_tokens != NULL)
    {
        if (identified_tokens->token_type == TOKEN_CMD)
            token_type = "COMMAND";
        else if (identified_tokens->token_type == TOKEN_LIMITER)
            token_type = "LIMITER";
        else if (identified_tokens->token_type == TOKEN_REDIRECT_IN)
            token_type = "REDIRECT_IN";
        else if (identified_tokens->token_type == TOKEN_REDIRECT_OUT)
            token_type = "REDIRECT_OUT";
        else if (identified_tokens->token_type == TOKEN_APPEND)
            token_type = "APPEND";
        else if (identified_tokens->token_type == TOKEN_HEREDOC)
            token_type = "HERE_DOC";
        else if (identified_tokens->token_type == TOKEN_PIPE)
            token_type = "PIPE";
        else if (identified_tokens->token_type == TOKEN_FILE)
            token_type = "FILE";
        printf("[%s] -> %s\n", identified_tokens->token_string, token_type);
        identified_tokens = identified_tokens->next;
		token_type = "TOKEN_NULL";
    }


    //check quotation
    printf("\nQUOTATION_CHECK\n");
    quotation_check(quotation_tokens);
    while (quotation_tokens != NULL)
    {
        printf("[%s] ", quotation_tokens->token_string);

        if (quotation_tokens->is_open_quoted == true)
            printf("open_quoted\n");
        else if (quotation_tokens->is_quoted == true)
            printf("quoted\n");
        else
            printf("unquoted\n");

        quotation_tokens = quotation_tokens->next;
    }

    // check expansion
    printf("\nEXPANSION_CHECK\n");
    token_expand(shell);
	expanded_tokens = shell->tokens;
    while (expanded_tokens != NULL)
    {
        printf("[%s]\n", expanded_tokens->token_string);
        expanded_tokens = expanded_tokens->next;
    }

    // quote remove
    printf("\nQUOTATION_REMOVE_CHECK\n");
    while (unquoted_tokens != NULL)
    {
        if (unquoted_tokens->is_quoted == true)
            quote_remove(unquoted_tokens->token_string);
        printf("[%s]\n", unquoted_tokens->token_string);
        unquoted_tokens = unquoted_tokens->next;
    }

	// check binary_tree
	if (user_input_parse(shell) == -1)
	{
		ft_token_lst_clear(&shell->tokens);
		return ;
	}

	btree_create(shell);
	tree = shell->tree;
	node_count = btree_node_count(tree);
	cmd_count = btree_cmd_count(tree);
	btree_print(tree, 60, true, cmd_count);
	btree_contents_print(tree, node_count, cmd_count);

	printf("\n");
}

void	export_check(t_shell *shell)
{
	int	i = 1;
	char *export[(shell->argc)];

	export[shell->argc - 1] = NULL;
	while (i < shell->argc)
	{
		export[i - 1] = shell->argv[i];
		i++;
	}
	i = 0;
	if (shell->argc > 1 && ft_bool_strcmp(shell->argv[1], "export") == true)
	{
		builtins_export(shell, export);
		export[0] = "export";
		export[1] = NULL;
		ft_printf("\n EXIT_CODE = %i\n\n", shell->exit_code);
		/*builtins_export(shell, export);
		  while (shell->env_vars[i])
		  ft_printf("%s\n", shell->env_vars[i++]);
		  free_array((void **)shell->env_vars, -1, true);
		  free_array((void **)shell->export_vars.m_array, -1, true);*/
	}
	ft_free_matrix(shell->env_vars);
	ft_free_matrix(shell->export_vars.m_array);
	exit(0);
}

void	unset_check(t_shell *shell)
{
	int		i = 2;
	char	*unset[(shell->argc - 1)];
	char	*export[2];

	unset[shell->argc - 2] = NULL;
	while (i < shell->argc)
	{
		unset[i - 2] = shell->argv[i];
		i++;
	}
	i = 0;
	if (shell->argc > 1 && ft_bool_strcmp(shell->argv[1], "unset") == true)
	{
		builtins_unset(shell, unset);
		export[0] = "export";
		export[1] = NULL;
		ft_printf("\n EXIT_CODE = %i\n\n", shell->exit_code);
		builtins_export(shell, export);
		  while (shell->env_vars[i])
			ft_printf("%s\n", shell->env_vars[i++]);
		free_array((void **)shell->env_vars, -1, true);
		free_array((void **)shell->export_vars.m_array, -1, true);
	}
	exit(0);
}

void	builtins_check(t_shell *shell)
{
	if (shell->argc == 1)
		return ;
	if (ft_bool_strcmp(shell->argv[1], "export") == true)
		export_check(shell);
	if (ft_bool_strcmp(shell->argv[1], "unset") == true)
		unset_check(shell);
}
// TESTING AREA END

	static
size_t	minishell_envp_size(t_shell *shell)
{
	size_t	size;

	size = 0;
	while (shell->envp[size])
		size++;
	return (size);
}

static int
shell_lvl_incr(t_shell *shell, char **new_var, char *old_var, char **tmp)
{
	int		lvl_int;

	(void) dup;
	lvl_int = ft_atoi(old_var + 6) + 1;
	if (lvl_int > 999)
	{
		if (shell->lvl_message == false)
		{
			shell->lvl_message = true;
			ft_printf_fd(2, LVLERR, lvl_int);
		}
		lvl_int = 1;
	}
	*tmp = ft_itoa(lvl_int);
	if (*tmp == NULL)
		return (-1);
	*new_var = ft_strjoin("SHLVL=", *tmp);
	free (*tmp);
	return (0);
}

static
void	shell_lvl_create(t_shell *shell, char **dup)
{
	dup[shell->env_size] = ft_strdup("SHLVL=1");
	if (dup[shell->env_size] == NULL)
		exit_clean(shell, 1, dup, NULL);
}

static
char	**minishell_env_dup(t_shell *shell, char *lvl)
{
	size_t	i;
	char	**dup;

	dup = malloc(sizeof(char *) * (shell->env_size + 2));
	if (dup == NULL)
		return (exit_clean(shell, 1, NULL, NULL), NULL);
	dup[shell->env_size] = NULL;
	dup[shell->env_size + 1] = NULL;
	i = 0;
	while (i < shell->env_size)
	{
		if (ft_bool_strncmp(shell->envp[i], "SHLVL", 5) == true)
		{
			if (shell_lvl_incr(shell, &dup[i], shell->envp[i], &lvl) == -1)
				return (exit_clean(shell, 1, dup, NULL), NULL);
		}
		else
			dup[i] = ft_strdup(shell->envp[i]);
		if (dup[i++] == NULL)
			return (exit_clean(shell, 1, dup, NULL), NULL);
		dup[i] = NULL;
	}
	if (lvl == NULL)
		shell_lvl_create(shell, dup);
	return (dup);
}

void	minishell_init(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->lvl_message = false;
	shell->argc = argc;
	shell->argv = argv;
	shell->envp = envp;
	shell->user_input = NULL;
	shell->exit_code = 0;
	shell->merge_ret = 0;
	shell->export_vars.m_array = NULL;
	shell->env_vars = NULL;
	shell->tokens = NULL;
	shell->tree = NULL;
	shell->env_size = minishell_envp_size(shell);
	shell->env_vars = minishell_env_dup(shell, NULL);
	shell->export_vars.length = shell->env_size;
	shell->export_vars.m_array = minishell_env_dup(shell, NULL);
	str_merge_sort(shell->export_vars, &shell->merge_ret);
	if (shell->merge_ret == -1)
		exit_clean(shell, 1, NULL, NULL);
}

void	iteration_clear(t_shell *shell)
{
	if (shell->tree != NULL)
		btree_clear(&shell->tree);
	if (shell->tokens != NULL)
		ft_token_lst_clear(&shell->tokens);
	str_merge_sort(shell->export_vars, &shell->merge_ret);
	if (shell->merge_ret == -1)
		return ; // SAFE EXIT
}

void	signal_prompt_setup(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_prompt);
}

void	signal_after_readline_setup(t_shell *shell)
{
	signal(SIGINT, SIG_IGN);
	if (g_last_signal == 130)
	{
		shell->exit_code = g_last_signal;
		g_last_signal = -1;
	}
}

int	preprocess_input(t_shell *shell)
{
	add_history(shell->user_input);
	user_input_parse(shell);
	token_lst_clear_safe(&shell->tokens);
	return (shell->tree != NULL);
}

int	handle_heredoc(t_shell *shell)
{
	int	stdin_save;

	stdin_save = dup(STDIN_FILENO);
	heredoc_find(shell->tree, shell->env_vars);
	safe_dup2(stdin_save, STDIN_FILENO);
	if (g_last_signal == 130)
	{
		shell->exit_code = g_last_signal;
		iteration_clear(shell);
		g_last_signal = -1;
		return (0);
	}
	return (1);
}

void	tree_execute(t_shell *shell)
{
	int	*stdfd;

	stdfd = stdfd_save();
	shell->exit_code = traverse_btree(shell->tree, shell);
	stdfd_restore(stdfd);
}

void    minishell_loop(t_shell *shell)
{
	while (TRUE)
	{
		signal_prompt_setup();
		shell->user_input = readline(PROMPT_MINISHELL);
		signal_after_readline_setup(shell);
		if (shell->user_input == NULL)
			break ;
		if (preprocess_input(shell) == 0)
			continue ;
		if (handle_heredoc(shell) == 0)
			continue ;
		tree_execute(shell);
		iteration_clear(shell);
	}
	rl_clear_history();
	ft_free_matrix(shell->env_vars);
	ft_free_matrix(shell->export_vars.m_array);
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc > 20)
		error_exit_argv(argv[1]);
	minishell_init(&shell, argc, argv, envp);
	builtins_logo();
	minishell_loop(&shell);
}
