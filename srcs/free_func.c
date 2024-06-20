/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beroy <beroy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:57:26 by beroy             #+#    #+#             */
/*   Updated: 2024/06/20 18:10:10 by beroy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_cmd(t_cmd *cmd)
{
	t_redir	*tmp;

	if (cmd->arg && cmd->arg[0])
		ft_splitdestroy(cmd->arg);
	if (cmd->line)
		free(cmd->line);
	while (cmd->redir != NULL)
	{
		tmp = cmd->redir->next;
		free(cmd->redir->arg);
		free(cmd->redir);
		cmd->redir = tmp;
	}
	if (cmd != NULL)
		free(cmd);
}

void	ft_free_all(t_head *head)
{
	t_env	*tmp;

	if (head->cmd != NULL)
		ft_free_cmd(head->cmd);
	while (head->env != NULL)
	{
		tmp = head->env->next;
		free(head->env->name);
		free(head->env->value);
		free(head->env);
		head->env = tmp;
	}
	if (head != NULL)
		free(head);
}
