/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:06:10 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/14 16:06:10 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_head *head)
{
	t_env	*copy;

	copy = head->env;
	if (head->cmd->arg[1])
	{
		ft_printf_fd(2, "env: '%s': No such file "\
						"or directory\n", head->cmd->arg[1]);
		return ;
	}
	while (copy)
	{
		printf("%s=%s\n", copy->name, copy->value);
		copy = copy->next;
	}
}
