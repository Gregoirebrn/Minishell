/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:19:51 by beroy             #+#    #+#             */
/*   Updated: 2024/07/08 14:47:24 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_is_empty(t_cmd *cmd, int full)
{
	int	i;
	int	ret;

	ret = 1;
	while (cmd)
	{
		i = 0;
		while (cmd->arg[i])
		{
			if (str_empty(cmd->arg[i]) == 0)
				ret = 0;
			i++;
		}
		if (full == 1 && redir_is_empty(cmd->redir) == 0)
			ret = 0;
		if (cmd->next == NULL)
			break ;
		cmd = cmd->next;
	}
	while (cmd->prev)
		cmd = cmd->prev;
	return (ret);
}

int	quote_skip(char *input, int *i, char find)
{
	*i += 1;
	while (input[*i] != 0 && input[*i] != find)
		*i += 1;
	if (input[*i] == 0)
		return (1);
	return (0);
}

int	check_line(char *input)
{
	int	i;

	i = 0;
	if (first_pipe(input) == 1)
		return (1);
	if (str_empty(input) == 1)
		return (1);
	if (check_redir_pipe(input) == 1)
		return (1);
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input[i + 1] == '|')
				return (1);
		}
		else if (input[i] == 34 || input[i] == 39)
		{
			if (quote_skip(input, &i, input[i]) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

t_cmd	*split_pipe(char *input)
{
	t_cmd	*cmd;
	t_cmd	*new;
	char	*extract;
	int		offset;
	int		i;

	offset = 0;
	i = 0;
	cmd = NULL;
	while (input[i])
	{
		find_pipe(input, &i);
		extract = ft_substr(input, offset, i - offset);
		if (extract == NULL)
			return (ft_free_cmd(&cmd), NULL);
		new = ft_cmd_new(extract);
		if (new == NULL)
			return (ft_free_cmd(&cmd), NULL);
		ft_cmdadd_back(&cmd, new);
		if (input[i] != 0)
			i++;
		offset = i;
	}
	return (cmd);
}

int	ft_parse(char *input, t_head *head)
{
	if (check_line(input) == 1)
		return (write(2, "bash: syntax error\n", 19), 1);
	head->cmd = split_pipe(input);
	if (head->cmd == NULL)
		return (1);
	if (space_redir(head->cmd) == 1)
		return (1);
	if (format_redir(head->cmd) == 1)
		return (1);
	if (format_var(head) == 1)
		return (1);
	format_backslash(head);
	if (split_ws(head->cmd) == 1)
		return (1);
	if (format(head) == 1)
		return (1);
	if (cmd_is_empty(head->cmd, 1) == 1)
		return (1);
	return (0);
}
