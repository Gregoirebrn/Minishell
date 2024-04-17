/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:19:51 by beroy             #+#    #+#             */
/*   Updated: 2024/04/17 14:36:14 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int quote_skip(char *input, int *i, char find)
{
	while (input[*i] != 0 && input[*i] != find)
		*i += 1;
	if (input[*i] == 0)
		printf("Quote unterminated");
}

int check_line(char *input)
{
	int i;
	int qc;

	i = 0;
	qc = 0;
	while (input[i])
	{
		if (input[i] == '|')
			if (input[i + 1] == '|')
				return (printf("double pipe not handled by minishell!"), 1);
		if (input[i] == 34)
		{
			qc++;
			quote_skip(input, &i, 34);
		}
		if (input[i] == 39)
		{
			qc++;
			quote_skip(input, &i, 39);
		}
		i++;
	}
	if (qc % 2 != 0)
		return (printf("quote unterminated!"), 1);
	return (0);
}

t_head	*ft_parse(char *input)
{
	if (check_line(input) == 1)
		return (NULL);
}
