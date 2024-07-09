/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:03:36 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/09 14:16:20 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_unset(t_head *head)
{
	int		i;

	if (head->cmd->next || !head->cmd->arg[1])
		return ;
	i = 1;
	while (head->cmd->arg[i])
	{
		rem_env(&head->env, head->cmd->arg[i], &ft_strcmp);
		i++;
	}
}

void	free_rem(t_env *remove)
{
	ft_free(remove->name);
	ft_free(remove->value);
	ft_free(remove);
}

void	rem_env(t_env **env, void *ref, int (*cmp)(char *, const char *))
{
	t_env	*remove;
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!(*cmp)(current->name, ref))
		{
			remove = current;
			current->prev = current->prev->prev;
			free_rem(remove);
			current = current->next;
			if (!current)
			{
				current = NULL;
				return ;
			}
		}
		current = current->next;
	}
//	current = *env;
//	if (current && (*cmp)(current->name, ref) == 0)
//	{
//		*env = current->next;
//		if (current->next)
//			current->next->prev = NULL;
//		free_rem(current);
//	}
}
