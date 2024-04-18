/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:19:51 by beroy             #+#    #+#             */
/*   Updated: 2024/04/17 19:07:39 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void quote_skip(char *input, int *i, char find)
{
	*i += 1;
	while (input[*i] != 0 && input[*i] != find)
		*i += 1;
	if (input[*i] == 0)
		printf("Quote unterminated");
}

int check_line(char *input)
{
	int i;


	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
				return (printf("double pipe not handled by minishell!\n"), 1);
		}
		else if (input[i] == 34)
			quote_skip(input, &i, 34);
		else if (input[i] == 39)
			quote_skip(input, &i, 39);
		i++;
	}
	return (0);
}

t_head	*ft_parse(char *input)
{
	if (check_line(input) == 1)
		return (NULL);
	return (NULL);
}
