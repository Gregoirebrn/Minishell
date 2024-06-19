/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:16:23 by beroy             #+#    #+#             */
/*   Updated: 2024/06/19 14:17:17 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	*i += 1;
}
