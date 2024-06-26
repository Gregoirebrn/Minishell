/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/26 18:59:30 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_var_heredoc(char *str, t_head *head)
{
	int		start;
	int		end;
	char	*value;
	char	*dup;

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
	if (!copy || !copy->redir->arg || !copy->redir->arg[0])
		return (0);
	if (unlink("tmp"))
		return (perror("unlink"), 1);
	return (0);
}

int	here_read_print(char *eof, t_cmd *copy, t_head *head)
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
		write(copy->redir->fd, str, ft_strlen(str));
		write(copy->redir->fd, "\n", 1);
		free(str);
	}
	return (0);
}

int	heredoc(t_head *head)
{
	t_cmd	*copy;

	copy = head->cmd;
	while (copy)
	{
		if (copy->redir && copy->redir->type == 4)
			break ;
		copy = copy->next;
	}
	if (!(copy && copy->redir && copy->redir->type == 4))
		return (1);
	if (!copy->redir->arg || !copy->redir->arg[0])
		return (write(2, "bash: syntax error "\
		"near unexpected token `newline'\n", 51), 0);
	copy->redir->fd = open("tmp", O_WRONLY | O_CREAT, 0644);
	sig_main(head, 2);
	if (here_read_print(head->cmd->redir->arg, copy, head))
		return (0);
	return (1);
}
