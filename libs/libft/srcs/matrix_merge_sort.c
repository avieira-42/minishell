#include "../include/libft.h"

void	matrix_merge_sort(t_array middle)
{
	t_array	left;
	t_array	right;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (middle.length > 1)
	{
		left.length = middle.length / 2 ;
		right.length = middle.length / 2 + middle.length % 2;
		left.m_array = malloc(left.length * sizeof(char *));
		right.m_array = malloc(right.length * sizeof(char *));
		if (!left.m_array || !right.m_array)
			return (ft_free_matrix(left.m_array), ft_free_matrix(right.m_array));
		while (i < left.length && middle.m_array[j])
			left.m_array[j++] = middle.m_array[i++];
		j = 0;
		while (i < middle.length && middle.m_array[j])
			right.m_array[j++] = middle.m_array[i++];
		matrix_merge_sort(left);
		matrix_merge_sort(right);
		matrix_merge(left, middle, right);
	}
}

void	matrix_merge(t_array left, t_array middle, t_array right)
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
	t_array		middle;

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
	middle.i_array = NULL;
	middle.c_array = NULL;
	matrix_merge_sort(middle);
	while (i < argc - 1)
		ft_printf("%s, ", argv[i++]);
}*/
