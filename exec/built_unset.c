/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:03:36 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/09 16:15:07 by grebrune         ###   ########.fr       */
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
	t_env	*tmp;

	tmp = *env;
	if ((*cmp)((*env)->name, ref) == 0)
	{
		*env = (*env)->next;
		(*env)->prev = NULL;
		return (free_rem(tmp), (void)0);
	}
	while (tmp)
	{
		if ((*cmp)(tmp->name, ref) == 0)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			return (free_rem(tmp), (void)0);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}
