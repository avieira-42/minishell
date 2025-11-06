/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_merge_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 08:58:36 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/06 18:43:41 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static
void	str_merge_sort_init(t_str_array *middle, t_str_array *left,
		t_str_array *right, int *ret)
{
	left->length = middle->length / 2 ;
	right->length = middle->length / 2 + middle->length % 2;
	left->m_array = malloc(left->length * sizeof(char *));
	if (left->m_array == NULL)
		return ;
	right->m_array = malloc(right->length * sizeof(char *));
	if (right->m_array == NULL)
	{
		free(left->m_array);
		left->m_array = NULL;
		*ret = -1;
		return ;
	}
}

void	str_merge_sort(t_str_array middle, int *ret)
{
	t_str_array	left;
	t_str_array	right;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (middle.length > 1)
	{
		str_merge_sort_init(&middle, &left, &right, ret);
		if (*ret == -1)
			return ;
		while (i < left.length && middle.m_array[j])
			left.m_array[j++] = middle.m_array[i++];
		j = 0;
		while (i < middle.length && middle.m_array[j])
			right.m_array[j++] = middle.m_array[i++];
		str_merge_sort(left, ret);
		str_merge_sort(right, ret);
		str_merge(left, middle, right);
	}
}

void	str_merge(t_str_array left, t_str_array middle, t_str_array right)
{
	int		l;
	int		m;
	int		r;

	l = 0;
	m = 0;
	r = 0;
	while (m < middle.length)
	{
		if (l < left.length && r < right.length
				&& ft_strcmp(left.m_array[l], right.m_array[r]) <= 0)
			middle.m_array[m++] = left.m_array[l++];
		else if (r < right.length && l < left.length
				&& ft_strcmp(right.m_array[r], left.m_array[l]) <= 0)
			middle.m_array[m++] = right.m_array[r++];
		else if (l < left.length && r >= right.length)
			middle.m_array[m++] = left.m_array[l++];
		else if (r < right.length && l >= left.length)
			middle.m_array[m++] = right.m_array[r++];
	}
	free(left.m_array);
	free(right.m_array);
}
/* NEED TO CHECK ALL THE MALLOCS CREATED WITH MERGE SORT
 * HOW TO HANDLE WHEN A LOT OF MALLOCS WERE CREATED RECURSIVELY AND ONE FAILS?*/
/*int  main(int argc, char **argv)
{
	int			i;
	int			j;
	t_str_array		middle;

	i = 0;
	j = 0;
	middle.length = argc - 1;
	while (j < argc - 1)
	{
		argv[j] = argv[j + 1];
		j++;
	}
	argv[j] = NULL;
	middle.m_array = argv;
	int ret = 0;
	str_merge_sort(middle, &ret);
	while (i < argc - 1)
		ft_printf("%s, ", argv[i++]);
	printf("\n%i\n", ret);
}*/
