/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grebrune <grebrune@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:04:21 by grebrune          #+#    #+#             */
/*   Updated: 2024/04/18 18:28:36 by grebrune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_old_pwd(t_head *head, char *old_pwd)
{
	t_env	*copy;

	copy = head->env;
	while (copy->next != NULL)
	{
		if (ft_strncmp(copy->name, "OLDPWD", 7))
		{
			free(copy->value);
			copy->value = old_pwd;
		}
		copy = copy->next;
	}
}

void	replace_var(char **arg, char *result)
{
	int		z;

	free(*(arg));
	*arg = calloc((strlen(result) + 1), sizeof (char));
	z = 0;
	while (result[z])
	{
		*(arg[z]) = result[z];
		z++;
	}
	*(arg[z]) = '\0';
}
