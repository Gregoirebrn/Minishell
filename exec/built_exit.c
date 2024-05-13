/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:28:49 by grebrune          #+#    #+#             */
/*   Updated: 2024/05/13 18:50:16 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		strnum(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

void	is_num(t_head *head)
{
	if (head->cmd->arg[2])
	{
		printf("bash: exit: numeric argument required\n");
		g_error = 1;
		return ;
	}
	else
	{
		exit(ft_atoi(head->cmd->arg[1]) % 256);
	}
}

void	ft_exit(t_head *head)
{
	t_cmd	*copy;

	if (!head->cmd->next)
		printf("exit\n");
	if (!head->cmd->arg[1])
	{
		ft_free_all(head);
		exit (0);
	}
	copy = head->cmd;
	if (strnum(copy->arg[1]))
	{
		is_num(head);
		return ;
	}
	ft_putstr_fd("bash: exit: %s: numeric argument required\n", copy->arg[1]);
	ft_free_all(head);
	exit (2);
}