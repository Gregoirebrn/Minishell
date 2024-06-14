/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:03:36 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/14 16:03:36 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_head *head)
{
	if (head->cmd->next || !head->cmd->arg[1])
		return ;
	rem_env(&head->env, head->cmd->arg[1], &ft_strcmp);
}

void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *))
{
	t_env	*remove;
	t_env	*current;

	current = *env;
	while (current && current->next)
	{
		if ((*cmp)(current->next->name, ref) == 0)
		{
			remove = current->next;
			current->next = current->next->next;
			free(remove->name);
			free(remove->value);
			free(remove);
		}
		current = current->next;
	}
	current = *env;
	if (current && (*cmp)(current->name, ref) == 0)
	{
		*env = current->next;
		free(current->value);
		free(current->name);
		free(current);
	}
}
