/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 20:15:33 by avieira-          #+#    #+#             */
/*   Updated: 2025/09/26 20:54:55 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void    tokenize_double_quoted_text(char **token, char *input, int *i)
{
    while (input[*i] != '\0'
}

void    tokenize_input(char **tokens, char *input)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(input[i] != '\0')
    {
        if (input[i] == '"')
            tokenize_double_quoted_text(tokens, &input[i], &i);
    }
}

