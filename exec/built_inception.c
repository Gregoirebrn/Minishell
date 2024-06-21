/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_inception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:13:12 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/21 19:29:36 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	mini_inception(t_head *head, int value)
{
	int		sh;
	char	*shlvl;

	shlvl = value_of_name(head->env, "SHLVL");
	sh = ft_atoi(shlvl);
	sh += value;
	shlvl = ft_itoa(sh);
	replace_value(head, shlvl, "SHLVL");
}

void	exit_shlvl(t_head*head, int shlvl, int status)
{
	shlvl--;
	if (shlvl <= 0)
	{
		free_fnp(head, head->fnp);
		ft_free_all(head);
		exit (status);
	}
	else
	{
		mini_inception(head, -1);
	}
}