/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira- <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 03:43:59 by avieira-          #+#    #+#             */
/*   Updated: 2025/09/25 04:29:19 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// COMMAND
# define CMD "cmd"

// OPERATOR
# define PIPE "|"
# define AND "&&"
# define OR "||"
# define READ "<"
# define APPEND ">"
# define HERE_DOC "<<"
# define REDIRECT ">>"

// STRING_LITERAL
# define STRING "string"

// FILE
# define FILE "file"

// CHARACTER
# define BACK_SLASH '\\'


/* where the functions regarding the seperation of tokens (categories of a string) will be 
 *
 * lets look at :
 * infile < ls -l | grep -H ".h" * | vim > outfile && mkdir header_modules
 * infile = file
 * < = operator
 * ls -l = command
 * | = operator
 * grep -H = command 
 * ".h" = string
 * | = operator
 * vim = cmd */

#endif
