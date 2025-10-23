#include "../minishell.h"

void	safe_close(int *fd_ptr)
{
	if (*fd_ptr != -1)
	{
		close (*fd_ptr);
		*fd_ptr = -1;
	}
}

void	free_array(void **array, int size, int free_ptr)
{
	int		i;
	void	**array_copy;

	if (array == NULL)
		return ;
	array_copy = array;
	i = 0;
	if (size < 0)
	{
		while (*array != NULL)
		{
			free(*array);
			*array++ = NULL;
		}
		free(*array);
	}
	else
	{
		while (i < size)
		{
			free(array[i]);
			array[i++] = NULL;
		}
		free(array[i]);
	}
	if (free_ptr > 0)
		free(array_copy);
}
