#include "minishell.h"

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
	if (btree_node == NULL)
		return ;
	if (btree_node->node_type == TOKEN_PIPE)
	{
		printf("NODE %i -> PIPE\n", *j);
		(*j)--;
	}
	else if (btree_node->node_type == TOKEN_CMD)
	{
		printf("NODE %i -> CMD\nargv: ", *i);
		(*i)--;
		while (*(btree_node->command->argv) != NULL)
		{
			printf("%s ", *(btree_node->command->argv));
			btree_node->command->argv++;
		}
		printf("\nredirect list: ");
		while (btree_node->command->redirects != NULL)
		{
			if (btree_node->command->redirects->redir_type == TOKEN_APPEND)
				printf(">> %s ", btree_node->command->redirects->filename);
			if (btree_node->command->redirects->redir_type == TOKEN_HEREDOC)
				printf("<< %s ", btree_node->command->redirects->filename);
			if (btree_node->command->redirects->redir_type == TOKEN_REDIRECT_IN)
				printf("> %s ", btree_node->command->redirects->filename);
			if (btree_node->command->redirects->redir_type == TOKEN_REDIRECT_OUT)
				printf("< %s ", btree_node->command->redirects->filename);
			btree_node->command->redirects = btree_node->command->redirects->next;
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

void    tokens_check(t_token_list *tokens, char **envp, char *user_input, t_btree **node)
{
	char            *token_type;
    t_token_list    *quotation_tokens;
    t_token_list    *expanded_tokens;
    t_token_list    *unquoted_tokens;
    t_token_list    *identified_tokens;
    t_token_list    *unidentified_tokens;
	t_token_list	*tree_tokens;
	t_btree			*tree;
	int				node_count;
	int				cmd_count;


    //check token speration
    printf("\nTOKENS_CHECK\n");
    tokenize_user_input(&tokens, user_input);
    quotation_tokens = tokens;
    expanded_tokens = tokens;
    unquoted_tokens = tokens;
    identified_tokens = tokens;
    unidentified_tokens = tokens;
    tree_tokens = tokens;
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
    token_expand(expanded_tokens, envp);
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
	if (user_input_parse(NULL, &tree_tokens) == -1)
	{
		printf("invalid_user_input\n");
		return ;
	}

	tree = btree_create(tree_tokens);
	node_count = btree_node_count(tree);
	cmd_count = btree_cmd_count(tree);
	btree_print(tree, 60, true, cmd_count);
	btree_contents_print(tree, node_count, cmd_count);

	*node = tree;
	printf("\n");
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

static
char	**minishell_env_dup(t_shell *shell)
{
	size_t	i;
	char	**dup;

	dup = malloc(sizeof(char *) * (shell->env_size + 1));
	if (dup == NULL)
		return NULL; // SAFE EXIT
	dup[shell->env_size] = NULL;
	i = 0;
	while (i < shell->env_size)
	{
		dup[i] = ft_strdup(shell->envp[i]);
		if (dup[i] == NULL)
		{
			free_array((void **)dup, -1, true);
			return (NULL); // SAFE EXIT
		}
		i++;
	}
	return (dup);
}

void	minishell_init(t_shell *shell, int argc, char **argv, char **envp)
{
	shell->argc = argc;
	shell->argv = argv;
	shell->envp = envp;
	shell->user_input = NULL;
	shell->exit_code = 0;
	shell->merge_ret = 0;
	shell->env_size = minishell_envp_size(shell);
	shell->env_vars = minishell_env_dup(shell);
	shell->export_vars.length = shell->env_size;
	shell->export_vars.m_array = minishell_env_dup(shell);
	str_merge_sort(shell->export_vars, &shell->merge_ret);
	if (shell->merge_ret == -1)
		return ; // SAFE EXIT
	shell->tokens = NULL;
	shell->tree = NULL;
}


void    minishell_loop(char **envp, t_shell *shell)
{

	int	i = 1;
	char *export[(shell->argc)];
    char *user_input;
    t_token_list *tokens;
	t_btree	*node;
	int		exit_code;
    user_input = NULL;
    tokens = NULL;
	export[shell->argc - 1] = NULL;
	while (i < shell->argc)
	{
		export[i - 1] = shell->argv[i];
		i++;
	}
	i = 0;


    while (TRUE)
    {
		// IMPLEMENT THE !! (last user_input join)
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
			return ;
		}
		user_input = readline(PROMPT_MINISHELL);
		if (user_input == NULL)
			break ;
		add_history(user_input);
		special_user_input_check(user_input);
		// tokenize command
		tokens_check(tokens, envp, user_input, &node);
		heredoc_find(node, envp);
		int pid = safe_fork();
		if (pid == 0)
			traverse_btree(node);
		waitpid(pid, &exit_code, 0);
		ft_printf("exit status: %d\n", WEXITSTATUS(exit_code));
		free(user_input);
		if (tokens != NULL)
			ft_token_lst_clear(&tokens);
		// >> alongside builtins >> (special_user_input_check(user_input)); <<
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
	draw_from_file(FILE_LOGO);
	minishell_loop(envp, &shell);
}
