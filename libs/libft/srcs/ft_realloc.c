/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:56:27 by avieira-          #+#    #+#             */
/*   Updated: 2025/11/07 15:01:27 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void    *ft_realloc(void *old_ptr, size_t new_size, size_t old_size)
{
    void    *new_ptr = NULL;
	size_t	cpy_size;

    new_ptr = malloc(new_size);
    if (new_ptr == NULL)
    {
        if (old_ptr != NULL)
            free(old_ptr);
        return (NULL);
    }
    if (old_ptr != NULL)
    {
		if (old_size < new_size)
			cpy_size = old_size;
		else
			cpy_size = new_size;
        ft_memcpy(new_ptr, old_ptr, cpy_size);
        free(old_ptr);
    }
    return (new_ptr);
}
/*int	main(int argc, char **argv)
{
	size_t	i;
	char	**split;

	if (argc < 3)
		return (1);
	split = ft_split(argv[1], ' ');
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	split = ft_realloc(split, sizeof(char *) * (i + 2), sizeof(char *) * (i + 1));
	split[i] = ft_strdup(argv[2]);
	split[i + 1] = NULL;
	i = 0;
	while (split[i])
	{
		printf("%s\n", split[i]);
		i++;
	}
	ft_free_matrix(split);
}*/
