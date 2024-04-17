/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:25 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/17 13:57:22 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_head *head)
{
	t_cmd	*copy;
	int		i;

	i = 0;
	copy = head->cmd;
	while (copy->next != NULL)
	{
		if (i == 1 && ft_strncmp(copy->arg[i], "-n")) // i == 1 si la commande echo est a arg[0] sinon i == 0
			i = -1;
		printf("%s ", copy->arg[i]);
		copy = copy->next;
		if (i > -1)
			i++;
	}
	if (copy != NULL && i != -1)
		printf("%s\n", copy->arg[i]);
	else
		printf("%s", copy->arg[i]);
}

void	ft_cd(t_head *head)
{
	// si le repertoire existe
	// si le user a les permissions
	//
}

void	ft_pwd(t_head *head)
{
	// prend le repertoire actuel
}

