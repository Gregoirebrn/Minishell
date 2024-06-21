/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:10:02 by beroy             #+#    #+#             */
/*   Updated: 2024/06/20 17:33:09 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_backslash(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str && str[j])
	{
		if (str[j] == '\\' && (str[j + 1] == '$'
				|| (j != 0 && str[j - 1] == '\\')))
			j++;
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = 0;
}

void	format_backslash(t_head *head)
{
	while (head->cmd)
	{
		remove_backslash(head->cmd->line);
		while (head->cmd->redir)
		{
			remove_backslash(head->cmd->redir->arg);
			if (head->cmd->redir->next == NULL)
				break ;
			head->cmd->redir = head->cmd->redir->next;
		}
		while (head->cmd->redir && head->cmd->redir->prev)
			head->cmd->redir = head->cmd->redir->prev;
		if (head->cmd->next == NULL)
			break ;
		head->cmd = head->cmd->next;
	}
	while (head->cmd->prev)
		head->cmd = head->cmd->prev;
}
