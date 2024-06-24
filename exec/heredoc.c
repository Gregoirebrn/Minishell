/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/24 13:00:56 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	here_read_print(char *eof, t_cmd *copy)
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
		write(copy->redir->fd, str, ft_strlen(str));
		write(copy->redir->fd, "\n", 1);
		free(str);
	}
	return (0);
}

int	heredoc(t_head *head)
{
	char	*eof;
	t_cmd	*copy;

	copy = head->cmd;
	while (copy)
	{
		if (copy->redir && copy->redir->type == 4)
			break ;
		copy = copy->next;
	}
	if (!(copy && copy->redir && copy->redir->type == 4))
		return (0);
	if (!copy->redir->arg)
		return (write(2, "bash: syntax error "\
		"near unexpected token `newline'\n", 51), -1);
	copy->redir->fd = open("tmp", O_WRONLY | O_CREAT, 0644);
	eof = copy->redir->arg;
	sig_main(head, 2);
	if (here_read_print(eof, copy))
		return (-1);
	return (1);
}
