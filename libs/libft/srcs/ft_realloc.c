/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 18:56:27 by avieira-          #+#    #+#             */
/*   Updated: 2025/10/10 20:58:19 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void    *ft_realloc(void *old_ptr, size_t size)
{
    char    *new_ptr;
    size_t  old_ptr_len;

    new_ptr = malloc(size);
    if (new_ptr == NULL)
    {
        if (old_ptr != NULL)
            free(old_ptr);
        return (NULL);
    }
    if (old_ptr != NULL)
    {
        old_ptr_len = ft_strlen(old_ptr);
        ft_memcpy(new_ptr, old_ptr, old_ptr_len + 1);
        free(old_ptr);
    }
    return (new_ptr);
}
