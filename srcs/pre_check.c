/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:45:58 by beroy             #+#    #+#             */
/*   Updated: 2024/06/17 17:13:04 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (0);
	if (c > 32 && c < 127)
		return (1);
	return (0);
}

int	check_before(char *input, int checked, int pos)
{
	int	i;

	i = checked;
	while (i < pos)
	{
		if (valid_char(input[i]) == 1)
			return (0);
		index_up(input, &i);
	}
	return (1);
}

int	check_after(char *input, int pos)
{
	int	i;

	i = pos + 1;
	while (input && input[i])
	{
		if (valid_char(input[i]) == 1)
			return (0);
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			break ;
		index_up(input, &i);
	}
	return (1);
}

int	check_redir_pipe(char *input)
{
	int		i;
	int		checked;
	char	find;

	i = 0;
	checked = 0;
	while (input && input[i])
	{
		if (input[i] == '<' || input[i] == '|' || input[i] == '>')
		{
			find = input[i];
			if (check_before(input, checked, i) == 1)
				return (1);
			if (input[i + 1] == find)
				i++;
			if (check_after(input, i) == 1)
				return (1);
			checked = i;
		}
		index_up(input, &i);
	}
	return (0);
}
