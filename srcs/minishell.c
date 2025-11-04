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
	int	m;

	m = 0;
	if (btree_node == NULL)
		return ;
	t_redirect	*redirects = btree_node->command->redirects;
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

t_token_list    *tokens_check(t_token_list *tokens, char **envp, char *user_input, t_btree **node)
{
	char            *token_type;
    t_token_list    *quotation_tokens;
    t_token_list    *expanded_tokens;
    t_token_list    *unquoted_tokens;
    t_token_list    *identified_tokens;
    t_token_list    *unidentified_tokens;
	t_token_list	*tree_tokens;
	t_token_list	*ret;
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
	ret = tokens;
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
		ft_token_lst_clear(&ret);
		return NULL;
	}

	tree = btree_create(tree_tokens);
	node_count = btree_node_count(tree);
	cmd_count = btree_cmd_count(tree);
	btree_print(tree, 60, true, cmd_count);
	btree_contents_print(tree, node_count, cmd_count);

	*node = tree;
	printf("\n");
	return (ret);
}

// TESTING AREA END

void    minishell_loop(char **envp)
{
	char *user_input;
	t_token_list *tokens;
	t_btree	*node;
	int		exit_code;

	user_input = NULL;
	tokens = NULL;
	while (TRUE)
	{
		user_input = readline(PROMPT_MINISHELL);
		if (user_input == NULL)
			break ;
		add_history(user_input);
		special_user_input_check(user_input);
		// tokenize command
		tokens = tokens_check(tokens, envp, user_input, &node);
		token_lst_clear_safe(&tokens);
		heredoc_find(node, envp);
		int pid = safe_fork();
		if (pid == 0)
			traverse_btree(node);
		waitpid(pid, &exit_code, 0);
		ft_printf("exit status: %d\n", WEXITSTATUS(exit_code));
		free(user_input);
		if (node != NULL)
			btree_clear(node);
		if (tokens != NULL)
			ft_token_lst_clear(&tokens);
		// >> alongside builtins >> (special_user_input_check(user_input)); <<
	}
	rl_clear_history();
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;

	if (argc != 1)
		error_exit_argv(argv[1]);
	draw_from_file(FILE_LOGO);
	minishell_loop(envp);
}
