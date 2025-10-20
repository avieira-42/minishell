void	safe_close(int *fd_ptr)
{
	if (*fd_ptr != -1)
	{
		close (*fd_ptr);
		*fd_ptr = -1;
	}
}