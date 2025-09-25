/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a-soeiro <avieira-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 00:46:29 by a-soeiro          #+#    #+#             */
/*   Updated: 2025/09/25 00:49:06 by avieira-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_removeline(char *buf)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = buf;
	while (buf[i] != '\n' && buf[i])
		i++;
	ptr += i;
	if (buf[i] == '\n')
		ptr++;
	i = 0;
	while (*ptr)
		buf[i++] = *(ptr++);
	while (buf[i])
		buf[i++] = '\0';
}

char	*ft_writeline(char *line, char *buf)
{
	int		len;
	char	*new_line;
	char	*l_ptr;
	char	*nl_ptr;

	if (!line && (!buf || !*buf))
		return (NULL);
	l_ptr = line;
	len = ft_nlen(line) + ft_nlen(buf);
	new_line = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (free(line), NULL);
	nl_ptr = new_line;
	while (l_ptr && *l_ptr)
		*(nl_ptr++) = *(l_ptr++);
	while ((nl_ptr - new_line < len))
		*(nl_ptr++) = *(buf++);
	*nl_ptr = '\0';
	return (free(line), new_line);
}

char	*get_next_line(int fd)
{
	ssize_t			bytes_read;
	char			*line;
	static char		buf[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	while (!ft_found_newline(line))
	{
		if (!*buf)
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read <= 0)
				break ;
		}
		line = ft_writeline(line, buf);
		if (!line)
			return (NULL);
		ft_removeline(buf);
	}
	if (!line)
		return (NULL);
	if (!line && *line == '\0')
		return (free(line), NULL);
	return (line);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	free(line);
}*/
