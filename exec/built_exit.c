/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:28:49 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/19 18:10:22 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_head *head)
{
	t_cmd	*copy;

	if (!head->cmd->next)
		write(2, "exit\n", 5);
	if (!head->cmd->arg[1])
	{
		free_fnp(head, head->fnp);
		ft_free_all(head);
		exit (0);
	}
	copy = head->cmd;
	if (ft_strnum(copy->arg[1]))
	{
		is_num(head);
		exit(1);
	}
	ft_printf_fd(2, "bash: exit: %s: "\
					"numeric argument required\n", copy->arg[1]);
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit (2);
}

int	ft_strnum(char *str)
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
		write(2, "bash: exit: numeric argument required\n", 38);
		g_error = 1;
		return ;
	}
	else
	{
		g_error = ft_atoi(head->cmd->arg[1]) % 256;
		exit(g_error);
	}
}
