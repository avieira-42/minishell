#ifndef CLEANING_H
# define CLEANING_H

# include "../types.h"

void	free_array(void **array, int size, int free_ptr);
void	safe_close(int *fd_ptr);
void	exit_clean(t_shell *shell, int exit_code, char **array, char *string);
void	close_all_fds(int fd_start, int fd_end);

#endif
