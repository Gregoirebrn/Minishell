/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:46:00 by grebrune          #+#    #+#             */
/*   Updated: 2024/06/12 13:46:00 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd_bis(t_head *head, char **str)
{
	if (head->cmd->arg[1] && head->cmd->arg[2])
		return (printf("Only one argument is taken by cd\n"), 2);
	if (head->cmd->arg[1])
	{
		get_path(str);
		*str = ft_strcat(*str, head->cmd->arg[1]);
	}
	else
	{
		cd_no_arg(head, str);
		if (!*str)
			return (printf("bash: cd: HOME not set\n"), 2);
	}
	if (*str == NULL)
		return (printf("Crash of Malloc\n"), 2);
	return (0);
}
