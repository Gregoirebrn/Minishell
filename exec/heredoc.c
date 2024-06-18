/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 17:45:32 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/18 14:20:27 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(t_head *head)
{
	char	*str;
	char	*eof;

	str = NULL;
	if (!(head->cmd->redir && head->cmd->redir->type == 2))
		return (0);
	//doesn't work do to parsing exiting before
	if (!head->cmd->redir->arg)
		return (ft_printf_fd(2, "bash: syntax error near unexpected token `newline'"), -1);
	//create tmp file
	head->cmd->redir->fd = open("tmp", O_WRONLY | O_CREAT, 0644);
	eof = head->cmd->redir->arg;
	while (42)
	{
		str = readline("> ");
		if (!str)
			return (write(2, "Error readline\n", 15), -1);
		if (ft_strcmp(str, eof) == 0)
		{
			write(2, "EOF found!\n", 11);
			free(str);
			break;
		}
		write(head->cmd->redir->fd, str, ft_strlen(str));
		write(head->cmd->redir->fd, "\n", 1);
		free(str);
		//add to pipe
	}
	write(2, "End of Heredoc\n", 15);
	return (1);
	//verifier le EOF si il est avec ou sans ""
	//gestion d'erreurs
}
