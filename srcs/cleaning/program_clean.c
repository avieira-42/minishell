#include "../minishell.h"

void	safe_close(int *fd_ptr)
{
	if (*fd_ptr != -1)
	{
		close(*fd_ptr);
		*fd_ptr = -1;
	}
}

static
void	free_null_array(void **array)
{
	while (*array != NULL)
	{
		free(*array);
		*(array++) = NULL;
	}
	free(*array);
}

static
void	free_sized_array(void **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		array[i++] = NULL;
	}
}

void	free_array(void **array, int size, int free_ptr)
{
	void	**array_copy;

	if (array == NULL)
		return ;
	array_copy = array;
	if (size < 0)
		free_null_array(array);
	else
		free_sized_array(array, size);
	if (free_ptr != 0)
		free(array_copy);
}
