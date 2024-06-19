/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:06:10 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/19 16:44:43 by grebrune         ###   ########.fr       */
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
		ft_putstr(head->cmd->arg[1]);
		write(2, "’: No such file or directory\n", 29);
		return ;
	}
	while (copy->next)
	{
		printf("%s=%s\n", copy->name, copy->value);
		copy = copy->next;
	}
	if (copy)
		printf("%s=%s\n", copy->name, copy->value);
	ft_exit(head);
}
