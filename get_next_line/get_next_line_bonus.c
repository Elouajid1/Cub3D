/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-ouaj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:29:39 by mel-ouaj          #+#    #+#             */
/*   Updated: 2024/11/27 16:18:32 by mel-ouaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_free(char *buffer)
{
	if (!buffer)
		return ;
	free (buffer);
}

char	*nline(char *buffer)
{
	int		i;
	int		j;
	char	*nbuf;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free(buffer), NULL);
	i++;
	nbuf = ft_calloc((ft_strlen(buffer) - i + 1), 1);
	if (!nbuf)
		return (ft_free(buffer), NULL);
	while (buffer[i])
	{
		nbuf[j] = buffer[i];
		i++;
		j++;
	}
	nbuf[j] = '\0';
	ft_free(buffer);
	return (nbuf);
}

char	*gline(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc(i + 2, 1);
	else
		line = ft_calloc(i + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_rfile(int fd, char *buffer)
{
	char	*buf;
	int		r;

	r = 0;
	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	buf = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buf)
		return (NULL);
	while (!(ft_strchr(buffer, '\n')))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (ft_free(buf), ft_free(buffer), NULL);
		if (r == 0)
			break ;
		buf[r] = 0;
		buffer = ft_strjoin(buffer, buf);
		if (!buffer)
			return (ft_free(buf), NULL);
	}
	ft_free(buf);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647 || fd > FD_MAX)
		return (NULL);
	buffer[fd] = ft_rfile(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = gline(buffer[fd]);
	buffer[fd] = nline(buffer[fd]);
	return (line);
}
