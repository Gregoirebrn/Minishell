/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:57:26 by beroy             #+#    #+#             */
/*   Updated: 2024/06/27 17:40:52 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_cmd(t_cmd **cmd)
{
	t_redir	*tmp_redir;
	t_cmd	*tmp_cmd;

	while ((*cmd))
	{
		tmp_cmd = (*cmd)->next;
		if ((*cmd)->arg)
			ft_splitdestroy((*cmd)->arg);
		if ((*cmd)->line)
			ft_free((*cmd)->line);
		while ((*cmd)->redir != NULL)
		{
			tmp_redir = (*cmd)->redir->next;
			ft_free((*cmd)->redir->arg);
			ft_free((*cmd)->redir);
			(*cmd)->redir = tmp_redir;
		}
		if ((*cmd) != NULL)
			ft_free(*cmd);
		(*cmd) = tmp_cmd;
	}
}

void	ft_free_all(t_head *head)
{
	t_env	*tmp;

	if (head->cmd != NULL)
		ft_free_cmd(&(head->cmd));
	while (head->env != NULL)
	{
		tmp = head->env->next;
		ft_free(head->env->name);
		ft_free(head->env->value);
		ft_free(head->env);
		head->env = tmp;
	}
	if (head != NULL)
		ft_free(head);
}
