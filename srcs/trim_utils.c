/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:54:15 by beroy             #+#    #+#             */
/*   Updated: 2024/06/21 14:20:52 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	trim_redir(t_head *head)
{
	while (head->cmd->redir)
	{
		if (nbr_quote(head->cmd->redir->arg) > 1)
			head->cmd->redir->quote = 1;
		head->cmd->redir->arg = trim_str(head->cmd->redir->arg);
		if (head->cmd->redir->arg == NULL)
			return (1);
		if (head->cmd->redir->next == NULL)
			break ;
		head->cmd->redir = head->cmd->redir->next;
	}
	while (head->cmd->redir->prev)
		head->cmd->redir = head->cmd->redir->prev;
	return (0);
}
