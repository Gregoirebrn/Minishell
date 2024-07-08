/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:28:49 by grebrune          #+#    #+#             */
/*   Updated: 2024/07/02 15:26:09 by grebrune         ###   ########.fr       */
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
		exit_free(head, g_error);
		return ;
	}
	copy = head->cmd;
	if (ft_strnum(copy->arg[1]))
	{
		if (is_num(head))
			return ;
		exit_free(head, 1);
		return ;
	}
	exit_write(copy->arg[1]);
	exit_free(head, 2);
}

void	exit_write(char *arg)
{
	write(2, "bash: exit: ", 12);
	write(2, arg, ft_strlen(arg));
	write(2, ": numeric argument required\n", 28);
}

int	ft_strnum(char *str)
{
	int	i;

	i = 0;
	if (!str || (str && !str[0]))
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str && str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (0);
		i++;
	}
	return (1);
}

int	is_num(t_head *head)
{
	if (head->cmd->arg[2])
	{
		write(2, "bash: exit: too many arguments\n", 31);
		g_error = 1;
		return (1);
	}
	else
	{
		g_error = ft_atoi(head->cmd->arg[1]) % 256;
		exit_free(head, g_error);
		return (0);
	}
}
