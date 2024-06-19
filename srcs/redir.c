/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:02:57 by beroy             #+#    #+#             */
/*   Updated: 2024/06/19 14:06:05 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
