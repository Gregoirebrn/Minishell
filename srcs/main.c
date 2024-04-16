/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:11:53 by beroy             #+#    #+#             */
/*   Updated: 2024/04/16 16:52:10 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_color(int i)
{
	if (i % 6 == 0)
		return (YELLOW);
	if (i % 6 == 1)
		return (GREEN);
	if (i % 6 == 2)
		return (CYAN);
	if (i % 6 == 3)
		return (BLUE);
	if (i % 6 == 4)
		return (PURPLE);
	else
		return (RED);
}

void	ft_header(void)
{
	char	*str;
	char	*color;
	int 	fd;
	int 	i;

	fd = open("data/header.txt", O_RDONLY);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		color = ft_color(i);
		printf("%s%s", color, str);
		str = get_next_line(fd);
		i++;
	}
	printf("\033[0m\n");
}

int	main(void)
{
	char	*input;

	ft_header();
	while (42)
	{
		input = readline("> ");
		printf("%s\n", input);
		add_history("input");
	}
}
