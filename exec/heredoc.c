/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/21 15:06:41 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_var_heredoc(char *str, t_head *head)
{
	int		start;
	int		end;
	char	*value;
	char 	*dup;

	start = find_var(str);
	end = find_end_var(str, start);
	value = var_value(str, start + 1, head->env);
	if (value == NULL)
		return (NULL);
	dup = str_dup_var(str, start, end, value);
	if (dup == NULL)
		return (NULL);
	return (dup);
}

int	expand_heredoc(char **str, t_head *head)
{
	while (find_var(*str) != -1)
	{
		*str = replace_var_heredoc(*str, head);
		if (*str == NULL)
			return (1);
	}
	return (0);
}

int	clear_heredoc(t_head *head)
{
	t_cmd	*copy;

	copy = head->cmd;
	while (copy)
	{
		if (copy->redir && copy->redir->type == 4)
			break ;
		copy = copy->next;
	}
	if (!copy)
		return (0);
	if (unlink("tmp"))
		return (perror("unlink"), 1);
	return (g_error = 0, 0);
}

int	here_read_print(char *eof, t_head *head)
{
	char	*str;

	while (42)
	{
		str = readline("> ");
		if (!str)
			return (write(2, "Error readline\n", 15), -1);
		if (ft_strcmp(str, eof) == 0)
		{
			free(str);
			break ;
		}
		if (head->cmd->redir->quote == 0)
		{
			if (expand_heredoc(&str, head) == 1)
				return (-1);
		}
		write(head->cmd->redir->fd, str, ft_strlen(str));
		write(head->cmd->redir->fd, "\n", 1);
		free(str);
	}
	return (0);
}

int	heredoc(t_head *head)
{
	if (!(head->cmd->redir && head->cmd->redir->type == 4))
		return (0);
	if (!head->cmd->redir->arg)
		return (write(2, "bash: syntax error "\
		"near unexpected token `newline'\n", 51), -1);
	head->cmd->redir->fd = open("tmp", O_WRONLY | O_CREAT, 0644);
	if (here_read_print(head->cmd->redir->arg, head))
		return (-1);
	return (1);
}
