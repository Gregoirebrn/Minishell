/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:45:58 by beroy             #+#    #+#             */
/*   Updated: 2024/06/28 16:00:01 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	first_pipe(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '|')
	{
		if (char_is_ws(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_pipe(char *input, int *i)
{
	int	nbr;

	nbr = 0;
	if (*i != 0 && input[*i - 1] == input[*i])
		nbr++;
	if (input[*i] == input[*i + 1])
		nbr++;
	if (nbr >= 2)
		return (1);
	return (0);
}

int	check_redir(char *input, int *i)
{
	int	nbr;

	nbr = 0;
	if (input[*i] == '<' && input[*i + 1] == '>')
		return (1);
	if (input[*i] == '>' && input[*i + 1] == '<')
		return (1);
	if (*i != 0 && input[*i - 1] == input[*i])
		nbr++;
	if (input[*i] == input[*i + 1])
		nbr++;
	if (nbr >= 2)
		return (1);
	return (0);
}

int	check_redir_pipe(char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '|')
			if (check_pipe(input, &i) == 1)
				return (1);
		if (input[i] == '<' || input[i] == '>')
			if (check_redir(input, &i) == 1)
				return (1);
		index_up(input, &i);
	}
	return (0);
}
