/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:00:16 by beroy             #+#    #+#             */
/*   Updated: 2024/06/26 20:22:45 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_type(char *line, int i)
{
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (2);
		else
			return (1);
	}
	else if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (4);
		else
			return (3);
	}
	else
		return (0);
}

int	find_redir(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (redir_type(line, i) != 0)
			return (1);
		index_up(line, &i);
	}
	return (0);
}

int	find_arg(char *line, int start)
{
	while (line[start] && char_is_ws(line[start]) == 1)
		index_up(line, &start);
	while (line[start] && char_is_ws(line[start]) == 0)
		index_up(line, &start);
	return (start - 1);
}

char	*dup_without_redir(char *line, int end)
{
	int		i;
	int		j;
	char	*dup;
	int		start;

	i = 0;
	j = 0;
	start = 0;
	while (redir_type(line, start) == 0)
		index_up(line, &start);
	dup = ft_calloc(ft_strlen(line) - end + start + 1, sizeof(char));
	if (dup == NULL)
		return (ft_free(line), NULL);
	while (line[i])
	{
		if (i == start)
			i = end + 1;
		dup[j] = line[i];
		if (line[i] != 0)
			i++;
		j++;
	}
	return (ft_free(line), dup);
}

int	extract_redir(t_cmd *cmd)
{
	int		start;
	int		end;
	int		type;
	t_redir	*new;

	start = 0;
	while (redir_type(cmd->line, start) == 0)
		index_up(cmd->line, &start);
	type = redir_type(cmd->line, start);
	if (type % 2 == 0)
		start += 2;
	else
		start++;
	while (char_is_ws(cmd->line[start]) == 1)
		start++;
	end = find_arg(cmd->line, start);
	new = ft_redir_new(cmd->line, start, end, type);
	if (new == NULL)
		return (1);
	ft_rediradd_back(&cmd->redir, new);
	cmd->line = dup_without_redir(cmd->line, end);
	if (cmd->line == NULL)
		return (1);
	return (0);
}
