/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:36:26 by beroy             #+#    #+#             */
/*   Updated: 2024/05/28 14:33:05 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_index_up(char *input, int *i)
{
	if (input[*i] == 39)
		quote_skip(input, i, 39);
	*i += 1;
}

void	tab_display(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		printf("tab %d: %s\n", i, tab[i]);
		i++;
	}
}

int spaces_to_add(char *str)
{
	int i;
	int spaces;

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

char *ft_dupwithspace(char *str)
{
	int 	spaces;
	int 	i;
	int		j;
	char	*dup;
	int 	quote;

	spaces = spaces_to_add(str);
	i = 0;
	j = 0;
	dup = calloc(ft_strlen(str) + spaces + 1, sizeof(char));
	quote = 0;
	if (dup == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			quote++;
		if (str[i] == '<' && quote % 2 == 0)
		{
			dup[j++] = ' ';
			dup[j++] = '<';
			if (str[i + 1] == '<')
			{
				dup[j++] = '<';
				i++;
			}
			dup[j++] = ' ';
		}
		else if (str[i] == '>' && quote % 2 == 0)
		{
			dup[j++] = ' ';
			dup[j++] = '>';
			if (str[i + 1] == '>')
			{
				dup[j++] = '>';
				i++;
			}
			dup[j++] = ' ';
		}
		else
			dup[j++] = str[i];
		i++;
	}
	return (free(str), dup);
}

int space_redir(t_cmd *cmd)
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