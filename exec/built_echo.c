/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:47:13 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/14 16:46:16 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_head *head, t_cmd *copy)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (!copy->arg[1])
	{
		printf("\n");
		return ;
	}
	if (0 == ft_strcmp(copy->arg[i], "-n"))
	{
		i++;
		n++;
	}
	if (ft_strcmp("$?", copy->arg[i]) == 0)
	{
		printf("%d", g_error);
		if (n == 0)
			printf("\n");
		exit(0);
	}
	print_tab(head, copy->arg, i, n);
}

void	print_tab(t_head *head, char **arg, int i, int n)
{
	while (arg[i])
	{
		printf("%s", arg[i]);
		i++;
	}
	if (n == 0)
		printf("\n");
	free_fnp(head, head->fnp);
	ft_free_all(head);
	exit(0);
}
