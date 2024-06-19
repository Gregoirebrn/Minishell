/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:03:41 by beroy             #+#    #+#             */
/*   Updated: 2024/06/19 14:09:09 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*str_dup_var(char *str, int s, int e, char *val)
{
	int		i;
	int		j;
	char	*dup;

	i = 0;
	j = 0;
	dup = ft_calloc(ft_strlen(str) - e + s + ft_strlen(val) + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (i < s)
		dup[j++] = str[i++];
	i = 0;
	while (val[i])
		dup[j++] = val[i++];
	while (str[e])
		dup[j++] = str[e++];
	return (free(str), free(val), dup);
}

int	replace_var_redir(char *str, t_head *head)
{
	int		start;
	int		end;
	char	*value;

	start = find_var(str);
	end = find_end_var(str, start);
	value = var_value(str, start + 1, head->env);
	if (value == NULL)
		return (1);
	head->cmd->redir->arg = str_dup_var(str, start, end, value);
	if (str == NULL)
		return (1);
	return (0);
}

int	format_var_redir(t_head *head)
{
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
	return (0);
}

int	format_var(t_head *head)
{
	while (head->cmd)
	{
		while (find_var(head->cmd->line) != -1)
		{
			if (replace_var_line(head->cmd->line, head) == 1)
				return (1);
		}
		if (format_var_redir(head) == 1)
			return (1);
		if (head->cmd->next == NULL)
			break ;
		head->cmd = head->cmd->next;
	}
	while (head->cmd->prev)
		head->cmd = head->cmd->prev;
	return (0);
}
