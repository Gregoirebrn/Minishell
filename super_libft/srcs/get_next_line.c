/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:34:48 by beroy             #+#    #+#             */
/*   Updated: 2024/01/17 16:18:34 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero_nl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		str[i] = 0;
		i++;
	}
}

char	*ft_line(int fd, int rd, char *line, char bf[OPEN_MAX][BUFFER_SIZE + 1])
{
	while (rd && ft_linecheck(line) == 0)
	{
		rd = read(fd, bf[fd], BUFFER_SIZE);
		if (rd < 0)
			return (ft_bzero_nl(bf[fd]), free(line), NULL);
		bf[fd][rd] = 0;
		line = ft_strjoin_nl(line, bf[fd]);
		if (line == NULL)
			return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			readed;

	readed = 1;
	if (fd < 0)
		return (NULL);
	if (read(fd, NULL, 0) < 0)
		return (ft_bzero_nl(buff[fd]), NULL);
	line = ft_strdup_nl(buff[fd]);
	if (line == NULL)
		return (NULL);
	line = ft_line(fd, readed, line, buff);
	if (line == NULL)
		return (NULL);
	ft_buffclean(buff[fd]);
	if (line[0] == 0)
		return (free(line), NULL);
	return (line);
}
