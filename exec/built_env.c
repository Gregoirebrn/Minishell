/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:06:10 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/21 19:06:36 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_head *head)
{
	t_env	*copy;

	copy = head->env;
	if (head->cmd->arg[1])
	{
		write(2, "env: '", 6);
		write(2, head->cmd->arg[1], ft_strlen(head->cmd->arg[1]));
		write(2, "’: No such file or directory\n", 31);
		free_fnp(head, head->fnp);
		ft_free_all(head);
		exit (0);
	}
	while (copy->next)
	{
		printf("%s=%s\n", copy->name, copy->value);
		copy = copy->next;
	}
	if (copy)
		printf("%s=%s\n", copy->name, copy->value);
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit (0);
}
