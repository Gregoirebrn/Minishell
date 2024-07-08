/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:16:23 by beroy             #+#    #+#             */
/*   Updated: 2024/07/08 14:53:09 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	str_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (char_is_ws(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	char_is_ws(char c)
{
	if ((c > 7 && c < 13) || c == ' ')
		return (1);
	return (0);
}

void	single_index_up(char *input, int *i)
{
	if (input[*i] == 39)
		quote_skip(input, i, 39);
	if (input[*i] != 0)
		*i += 1;
}

int	char_is_num(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	index_up(char *input, int *i)
{
	if (input[*i] == 34)
		quote_skip(input, i, 34);
	else if (input[*i] == 39)
		quote_skip(input, i, 39);
	if (input[*i] != 0)
		*i += 1;
}
