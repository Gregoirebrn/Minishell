/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/19 16:04:53 by grebrune         ###   ########.fr       */
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
			break;
		copy = copy->next;
	}
	if (!copy)
		return (0);
	if (unlink("tmp"))
		return (perror("unlink"), 1);
	return (g_error = 0, 0);
}

int	expand_or_not(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (i == 0 && str[i] != '"')
			return (1);
	}
	return (0);
}

//char	*expandible(t_head *head, char *str)
//{
//	if (expand_or_not(str))
//		return (str);
//	return (str);
//}

int	heredoc(t_head *head)
{
	char	*str;
	char	*eof;

	str = NULL;
	if (!(head->cmd->redir && head->cmd->redir->type == 4))
		return (0);
	//doesn't work do to parsing exiting before
	if (!head->cmd->redir->arg)
		return (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'"), -1);
	head->cmd->redir->fd = open("tmp", O_WRONLY | O_CREAT, 0644);
	eof = head->cmd->redir->arg;
	while (42)
	{
		str = readline("> ");
		if (!str)
			return (write(2, "Error readline\n", 15), -1);
		if (ft_strcmp(str, eof) == 0)
		{
			free(str);
			break;
		}
//		str = expandible(head, str);
		write(head->cmd->redir->fd, str, ft_strlen(str));
		write(head->cmd->redir->fd, "\n", 1);
		free(str);
	}
	return (1);
	//verifier le EOF si il est avec ou sans ""
	//gestion d'erreurs
}
