/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:06:10 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/24 16:09:22 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_head *head)
{
	t_env	*copy;
	int		i;

	if (!head->env)
		exit_free(head, 0);
	copy = head->env;
	i = checker_env(head->cmd->arg);
	if (i != 0)
	{
		write(2, "env: '", 6);
		write(2, head->cmd->arg[i], ft_strlen(head->cmd->arg[i]));
		write(2, "’: No such file or directory\n", 31);
		exit_free(head, 0);
	}
	while (copy->next)
	{
		printf("%s=%s\n", copy->name, copy->value);
		copy = copy->next;
	}
	if (copy)
		printf("%s=%s\n", copy->name, copy->value);
	exit_free(head, 0);
}

int	checker_env(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (ft_strcmp(arg[i], "env"))
			return (i);
		i++;
	}
	return (0);
}
