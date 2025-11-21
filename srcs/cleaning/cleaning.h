/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcesar-s <jcesar-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 21:44:29 by jcesar-s          #+#    #+#             */
/*   Updated: 2025/11/21 14:07:39 by jcesar-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANING_H
# define CLEANING_H

# include "../types.h"

void	free_array(void **array, int size, int free_ptr);
void	safe_close(int *fd_ptr);
void	exit_clean(t_shell *shell, int exit_code, char **array, char *string);
void	close_all_fds(int fd_start, int fd_end);
void	iteration_clear(t_shell *shell);
void	ft_exit(t_shell *shell);

#endif
