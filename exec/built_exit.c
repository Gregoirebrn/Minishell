/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:28:49 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/12 15:29:40 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	strnum(char *str)
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
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
		g_error = 1;
		return ;
	}
	else
	{
		g_error = ft_atoi(head->cmd->arg[1]) % 256;
		exit(g_error);
	}
}

void	ft_exit(t_head *head)
{
	t_cmd	*copy;

	if (!head->cmd->next)
		ft_putstr_fd("exit\n", 1);
	if (!head->cmd->arg[1])
	{
		ft_free_all(head);
		exit (0);
	}
	copy = head->cmd;
	if (strnum(copy->arg[1]))
	{
		is_num(head);
		exit(1);
	}
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(copy->arg[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	ft_free_all(head);
	exit (2);
}
