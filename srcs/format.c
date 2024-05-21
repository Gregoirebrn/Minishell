/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:00:48 by beroy             #+#    #+#             */
/*   Updated: 2024/05/21 18:11:14 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *trim_str(char *str)
{
	int		i;
	char	*trim;
	int 	len;

	i = 0;
	if (str[i] != 34 && str[i] != 39)
		return (str);
	len = (int)ft_strlen(str);
	trim = calloc(len - 2 + 1, sizeof(char));
	if (trim == NULL)
		return (NULL);
	while (i < len - 2)
	{
		trim[i] = str[i + 1];
		i++;
	}
	free(str);
	return (trim);
}

int trim_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		tab[i] = trim_str(tab[i]);
		if (tab[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

int format(t_head *head)
{
	while (head->cmd)
	{
		if (trim_tab(head->cmd->arg) == 1)
			return (1);
		if (head->cmd->next == NULL)
			break ;
		head->cmd = head->cmd->next;
	}
	while (head->cmd->prev)
		head->cmd = head->cmd->prev;
	return (0);
}

int	format_redir(t_cmd *cmd)
{
	while (cmd)
	{
		while (find_redir(cmd->line) == 1)
		{
			if (extract_redir(cmd) == 1)
				return (1);
		}
		if (cmd->next == NULL)
			break ;
		cmd = cmd->next;
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (0);
}

int format_var(t_head *head)
{
	while (head->cmd)
	{
		while (find_var(head->cmd->line) != -1)
		{
			if (replace_var_line(head->cmd->line, head) == 1)
				return (1);
		}
		while (head->cmd->redir)
		{
			while (find_var(head->cmd->redir->arg) != -1)
			{
				if (replace_var_redir(head->cmd->redir->arg, head) == 1)
					return (1);
			}
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
	return (0);
}
