#include "parsing.h"

t_token_list	*ft_token_lst_last(t_token_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_token_lst_add_back(t_token_list **lst, t_token_list *new_node)
{
	if (new_node)
	{
		if (*lst)
			ft_token_lst_last(*lst)->next = new_node;
		else
			*lst = new_node;
	}
}

void	ft_token_lst_clear(t_token_list **lst)
{
	t_token_list	*node;
	t_token_list	*tmp;

	node = *lst;
	while (node)
	{
		tmp = node->next;
        if (node->token_string != NULL)
		{
            free(node->token_string);
			node->token_string = NULL;
		}
        free(node);
		node = tmp;
	}
	*lst = NULL;
}

void	token_lst_clear_safe(t_token_list **lst)
{
	t_token_list	*node;
	t_token_list	*tmp;

	node = *lst;
	while (node)
	{
		if (is_operator(node->token_string))
			free(node->token_string);
		tmp = node->next;
        free(node);
		node = tmp;
	}
	*lst = NULL;
}

t_token_list	*ft_token_lst_new(char *token)
{
	t_token_list	*new_node;

	new_node = (t_token_list *) malloc(sizeof(t_token_list));
	if (!new_node)
		return (NULL);
    new_node->token_type = TOKEN_NULL;
	new_node->token_string = token;
    new_node->is_quoted = false;
    new_node->is_open_quoted = false;
	new_node->next = NULL;
	return (new_node);
}
