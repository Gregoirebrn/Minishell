/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:36:26 by beroy             #+#    #+#             */
/*   Updated: 2024/06/17 18:11:26 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	spaces_to_add(char *str)
{
	int	i;
	int	spaces;

	i = 0;
	spaces = 0;
	while (str[i])
	{
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			spaces += 2;
		}
		else if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			spaces += 2;
		}
		index_up(str, &i);
	}
	return (spaces);
}

void	ft_dupwithspace2(char *str, char *dup, int i, int j)
{
	char	quote;

	quote = 0;
	while (str[i])
	{
		if (quote == 0 && (str[i] == 34 || str[i] == 39))
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		if (quote == 0 && (str[i] == '<' || str[i] == '>'))
		{
			dup[j++] = ' ';
			dup[j++] = str[i];
			if (str[i + 1] == str[i])
			{
				dup[j++] = str[i];
				i++;
			}
			dup[j++] = ' ';
		}
		else
			dup[j++] = str[i];
		i++;
	}
}

char	*ft_dupwithspace(char *str)
{
	int		i;
	int		j;
	char	*dup;

	i = 0;
	j = 0;
	dup = ft_calloc(ft_strlen(str) + spaces_to_add(str) + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	ft_dupwithspace2(str, dup, i, j);
	return (ft_free(str), dup);
}

int	space_redir(t_cmd *cmd)
{
	while (cmd)
	{
		cmd->line = ft_dupwithspace(cmd->line);
		if (cmd->line == NULL)
			return (1);
		if (cmd->next == NULL)
			break ;
		cmd = cmd->next;
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (0);
}
