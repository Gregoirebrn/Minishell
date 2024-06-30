/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:55:35 by beroy             #+#    #+#             */
/*   Updated: 2024/06/20 17:55:35 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_color(int i)
{
	if (i % 6 == 0)
		return (ft_strdup(YELLOW));
	if (i % 6 == 1)
		return (ft_strdup(GREEN));
	if (i % 6 == 2)
		return (ft_strdup(CYAN));
	if (i % 6 == 3)
		return (ft_strdup(BLUE));
	if (i % 6 == 4)
		return (ft_strdup(PURPLE));
	else
		return (ft_strdup(RED));
}

void	ft_header(void)
{
	char	*str;
	char	*color;
	int		fd;
	int		i;

	fd = open("data/header.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		color = ft_color(i);
		printf("%s%s", color, str);
		ft_free (str);
		ft_free (color);
		str = get_next_line(fd);
		i++;
	}
	printf("\033[0m\n");
	close (fd);
}
